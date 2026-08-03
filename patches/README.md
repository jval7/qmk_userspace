# Parches locales sobre submódulos

Los submódulos de `modules/` apuntan a repositorios de terceros, así que sus
cambios locales **no se versionan con este repo**: `git submodule update`
los borra sin avisar. Los parches que hagan falta viven aquí y se reaplican
a mano.

## bk_pointing_device-encadenar-hook-usuario.patch

Añade una línea a `digitizer_task_kb` para que reenvíe a `digitizer_task_user`.

QMK encadena `_kb` -> `_user` por convención, pero este módulo sobrescribe
`digitizer_task_kb` y corta la cadena — su propio comentario reconoce que el
hook de usuario queda muerto. Esa llamada es el **único** punto donde los
contactos del digitizer son válidos: `digitizer_get_state()` desde
`housekeeping_task_user` devuelve el estado sin refrescar.

Sin este parche, el keymap `helm` deja de ver los dedos y por diseño degrada a
no hacer nada: se cae el filtro antideriva, el freno de la inercia y el clic
fijado con tres dedos. No falla ruidosamente, simplemente deja de funcionar.

Reaplicar con:

    git -C modules/bastardkb apply ../../patches/bk_pointing_device-encadenar-hook-usuario.patch

Comprobar que sigue aplicado:

    grep -n "digitizer_task_user(digitizer_state)" modules/bastardkb/bk_pointing_device/bk_pointing_device.c

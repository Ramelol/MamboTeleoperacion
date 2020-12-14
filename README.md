# MamboTeleoperacion
Este repositorio contiene los archivos correspondientes a la aplicación 'Mambo-Teleoperación', desarrollada en unity, que permite operar de forma remota un minidrone parrot con una interfaz de realidad aumentada. También se incluye el modelo de control del dron, en simulink, y el programa de recepción de información en matlab.

La carpeta App contiene tanto los archivos del proyecto en Unity como el apk de la aplicación para su instalación de forma directa. La carpeta Simulink contiene el programa de recepción de información, llamado "Lector.m" y el modelo de bloques de Simulink para cargar al dron en el archivo "FlyCode.prj" que se puede abrir desde Matlab.

Para abir el proyecto de Unity:

1. Descargue el archivo .zip correspondiente a la carpeta App

2. Descomprimalo en la ubicación que tenga definida como workspace de Unity

3. Abra Unity Hub

4. El proyecto app debería aparecer en el listado de proyectos de Unity Hub, de ser así lo puede abir dando clic en el nombre App, tenga en cuenta que debe seleccionar la versión 2018.4.26f1 LTS.

5. Si el proyecto no aparece en el listado, de doble clic en el botón ADD, se abrirá un navegador de archivos y allí podrá buscar la ubicación donde descomprimio los datos del proyecto y añadirlo al listado

6. Una vez abierto el proyecto en Unity podrá navegar entre las escenas, consultar los scripts en C#, ejecutar la simulación o cargar el apk a su móvil conectadolo al equipo por usb.

Para instalar la aplicación en su celular:

1. Descargue el archivo 'app.apk' de la carpeta app

2. Transfiera el archivo al celular en que desea instalar la aplicación

3. En la configuración del celular, active la opción de instalar desde fuentes desconocidas

4. Busque la ubicación del archivo 'app.apk' y abrálo. Iniciara la instalación de la aplicación

5. Deberá autorizar a la aplicación el uso de la cámara

6. Luego de esto espere hasta que finalice la instalación.

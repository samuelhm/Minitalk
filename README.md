
# Minitalk

**Minitalk** es un proyecto desarrollado como parte del plan de estudios de la escuela 42. El objetivo del proyecto es implementar un sistema de comunicación simple entre procesos utilizando señales en Unix. Este proyecto proporciona una experiencia práctica con señales y la gestión de procesos en sistemas Unix.

## Tabla de contenidos

- [Descripción](#descripción)
- [Estructura del Proyecto](#estructura-del-proyecto)
- [Compilación e Instalación](#compilación-e-instalación)
- [Uso](#uso)
- [Detalles Técnicos](#detalles-técnicos)
- [Autores](#autores)

## Descripción

El proyecto **Minitalk** consiste en crear dos programas: un **servidor** y un **cliente**. El cliente enviará una cadena de texto al servidor carácter por carácter utilizando señales de Unix (`SIGUSR1` y `SIGUSR2`). El servidor deberá reconstruir la cadena y mostrarla.

## Estructura del Proyecto

El proyecto se divide en dos programas principales:

- **Servidor**: Recibe los mensajes del cliente y los muestra en la salida estándar.
- **Cliente**: Envía una cadena de caracteres al servidor utilizando señales.

## Compilación e Instalación

1. **Clona el repositorio**:
   ```bash
   git clone https://github.com/samuelhm/Minitalk.git
   cd Minitalk
   ```

2. **Compila los programas** usando el comando `make`:
   ```bash
   make
   ```

   Esto generará los archivos ejecutables `server` y `client`.

## Uso

Para ejecutar los programas, primero inicia el **servidor** y toma nota del **PID** que se muestra en la terminal:

```bash
./server
```

A continuación, ejecuta el **cliente** pasando el PID del servidor y el mensaje que deseas enviar:

```bash
./client <PID_del_servidor> "Mensaje a enviar"
```

Por ejemplo:

```bash
./server
```

En otra terminal:

```bash
./client 12345 "Hola desde el cliente!"
```

El servidor mostrará:

```
Hola desde el cliente!
```

## Detalles Técnicos

- El proyecto utiliza las señales `SIGUSR1` y `SIGUSR2` para enviar datos binarios del cliente al servidor.
- Se implementan técnicas de manejo de señales, pausa de procesos y uso de handlers.
- El envío de cada carácter se convierte en una secuencia de bits que se transmite utilizando las señales mencionadas.

## Autores

- **Samuel H. M.** - [GitHub](https://github.com/samuelhm)


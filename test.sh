#!/bin/bash

server=$(pgrep server)

if [ -z "$server" ]; then
  echo "Error: No se encontró el proceso 'server'. Asegúrate de que esté en ejecución."
  exit 1
fi

echo "Probando Minitalk en modo secuencial"
echo "PID del servidor: $server"

# Pruebas secuenciales
for i in {1..5}; do
  ret=$(./client "$server" "Mensaje $i")
  echo "Test $i: Retorno: $ret"
done

echo "Pulsa [Enter] para probar en modo asincrónico..."
read

# Pruebas asincrónicas
for i in {1..25}; do
  ret=$(./client "$server" "Mensaje $i" &)
  echo "Test Asincrónico $i: Retorno: $ret"
done

# Esperar a que todos los procesos en segundo plano terminen
wait
echo "Pruebas completadas."

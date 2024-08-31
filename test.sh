#!/bin/bash

for i in {1..10}; do
  ./client 14570 "Mensaje $i" &
done
wait

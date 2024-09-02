#!/bin/bash

for i in {1..700}; do
  ./client 31677 "Mensaje $i" &
done


#!/bin/bash

for i in {1..10}; do
  ./client 23960 "Mensaje $i"
done


#!/bin/bash
PORT=${1:-8080}
for i in {1..5}; do
  curl -s http://localhost:$PORT/ &
done
wait
echo "done"

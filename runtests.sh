#!/bin/bash

echo "\nIniciando..."
NUMTEST="1"
while [ "${NUMTEST}" -lt "14" ]; do
  if [ "${NUMTEST}" -lt "10" ]; then NUMTEST="0${NUMTEST}"; fi

  ./principal < test/${NUMTEST}.in > test/${NUMTEST}.sal
  diff test/${NUMTEST}.out test/${NUMTEST}.sal
  
  if [ "$?" != "0" ]; then
    echo "Error en el test #${NUMTEST}"
    echo "\nEntrada:"
    cat -n test/${NUMTEST}.in
    break
  fi
  
  NUMTEST="$(expr "$NUMTEST" "+" "1")"
done
echo "Fin"

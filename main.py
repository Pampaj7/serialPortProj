import serial
import random
import time

# Imposta la porta seriale e il baud rate
ser = serial.Serial('COM4', 9600)

##
# while True:
#   value = random.randint(0, 255)
#  ser.write(value.to_bytes(1, byteorder='big'))  # Invia l'intero sulla porta seriale
# time.sleep(0.1)

while True:
    tipo_dispositivo = 'LAMP'  # Tipo di dispositivo
    intensita = random.randint(0, 1000)  # Intensità casuale

    messaggio = tipo_dispositivo + '{:04d}'.format(intensita)  # Crea il messaggio da inviare

    ser.write(messaggio.encode())

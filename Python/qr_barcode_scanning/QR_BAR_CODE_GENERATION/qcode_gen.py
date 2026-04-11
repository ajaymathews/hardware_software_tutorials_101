import pyzbar
import pyqrcode
from qrtools.qrtools import QR

qr = pyqrcode.create("HAPPY ONAM")
qr.png("ONAM.png", scale=10)


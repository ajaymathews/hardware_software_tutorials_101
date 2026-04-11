import barcode
from barcode.writer import ImageWriter
code128 = barcode.get('CODE128', 'ABCD', writer=ImageWriter())
#ean = barcode.get('EAN8', '12345678', writer=ImageWriter())#EAN-8 barcode with maximum of 8 nos.
filename = code128.save('barcode_code128')
'''
commonly used barcode are
EAN-8
EAN-13
EAN-14
UPC-A
JAN
ISBN-10
ISBN-13
ISSN
Code 39
Code 128
PZN
'''

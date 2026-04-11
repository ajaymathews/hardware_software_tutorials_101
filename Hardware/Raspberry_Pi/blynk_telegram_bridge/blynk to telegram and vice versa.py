from telegram.ext import Updater, CommandHandler, MessageHandler, Filters,CallbackQueryHandler
from telegram import InlineKeyboardButton,InlineKeyboardMarkup
#import RPi.GPIO as GPIO    # Import Raspberry Pi GPIO library
import time 
import BlynkLib
import telegram
g=0
blynk = BlynkLib.Blynk('a462d0622a094db497cac4c5abaa983c')
@blynk.VIRTUAL_WRITE(1)
def my_write_handler(value):
    print('Current V1 value: {}'.format(value))
    global g
    g=int(value[0])
def start(bot, update):
    print("started")
    kb = [['/BUTTON']]
    kb_markup = telegram.ReplyKeyboardMarkup(kb)
    bot.send_message(chat_id=update.message.chat_id,text="select the option ",reply_markup=kb_markup)
    name=update.message.chat.first_name
    print("end of start")
    # this widget will show some time in seconds..
    blynk.virtual_write(2,name)
def button(bot,update):
    global g
    print("buttoned")
    print('Current V1 value: {}',g)
    update.message.reply_text(g)
    #bot.send_message(chat_id=update.message.chat_id,text=g,reply_markup=kb_markup)
    print(g)
    print("end of button")

bot=telegram.Bot(token='749056757:AAEQUeuOzXI7S91apHf0RkMeIsIiA24ZRr4')
updater = Updater(token='749056757:AAEQUeuOzXI7S91apHf0RkMeIsIiA24ZRr4')
dispatcher = updater.dispatcher
print("Bot started")
start_handler = CommandHandler('start', start)
dispatcher.add_handler(start_handler)
button_handler = CommandHandler('BUTTON', button)
dispatcher.add_handler(button_handler)
updater.start_polling()
#updater.idle()
while 1:
    blynk.run()

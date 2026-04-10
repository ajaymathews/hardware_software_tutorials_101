name=[]
password=[]
balance=[]

#definition of homepage
def main():
    choice=int(input("What would you like to login as..  \n 1.Admin \n 2.User"))
    count=0
    if choice == 1:
        admin()
    elif choice == 2:
        user()
    else:
        print("invalid choice")
        print("\n")
        main()
        

#adiministrator code
def admin():
    print("welcome Administrator  !")
    achoice=int(input("Want you like to do \n 1.Create ClientId \n 2.Remove an existing Client \n 3.View Status of Client \n 4.Exit"))
    if achoice==1:
        create_client()
    elif achoice==2:
        remove_client()
    elif achoice==3:
        status_client()
    elif achoice==4:
        main()
    else :
        if count<2:
            count=count+1
            print("Invalid choice... \n Please select correct option")
            print("\n")
            admin()
        else:
            print("You have entered wrong choice multiple times..")
            print("\n")
            main()

#code to create client
def create_client():
    aname=input("Client Id please:")
    fcreate=open("bank_client.txt","a")
    fcreate.close()
    fcheck=open("bank_client.txt","r")
    strname=fcheck.read()
    name=strname.split(".")
    fcheck.close()
    if aname in name:
        print("Username already exists\n")
        aname=input("enter another name please:\n")
    apass=input("you may enter user password:")
    apass1=input("Please enter the user password again:")
    while not apass==apass1:
        print("Passwords doesnt match")
        apass1=input("Please enter the user password again:")
    balanc=input("current amount please:")
    fnew=open("bank_client.txt","a")
    fnew.write(aname)
    fnew.write(".")
    fnew.write(apass)
    fnew.write(".")
    fnew.write(balanc)
    fnew.write(".")
    fnew.close()
    print("client successfully created")
    print("\n")
    admin()

#code to remove client
def remove_client():
    fremove=open("bank_client.txt","r")
    strname=fremove.read()
    name=strname.split(".")
    fremove.close()
    limit=(len(name))
    i = 0
    while i<=limit:
        print(name[i])
        i = i + 3
    del_name=input("Type the ClientId you want to delete:")
    while not del_name in name:
        if del_name=='exit':
            admin()
        else:
            print("we cant find the Client you entered")
            del_name=input("Please Enter again the User You want to delete:")
    inde=name.index(del_name)
    #print(inde)
    name[inde]=""
    name[inde+1]=""
    name[inde+2]=""
    fdelete=open("bank_client.txt","w")
    #list1 = ['1', '2', '3']
    dename='.'.join(name)
    fdelete.write(dename)
    fdelete.close()
    print("client successfully deleted")
    print("\n")
    admin()

#code to show status
def status_client():
    fstatus=open("bank_client.txt","r")
    strname=fstatus.read()
    name=strname.split(".")
    fstatus.close()
    limit=(len(name))
    i = 0
    while i <=limit:
        print(name[i])
        i = i + 3
    stat_name=input("Type the UserName You want to Check:")
    while not stat_name in name:
        
        if stat_name == 'exit':
            admin()
        else:
            print("we cant find the User You Entered \n")
            stat_name=input("Please Enter again the User You want to check:")
            
    inde=name.index(stat_name)
    print("client name:")
    print(stat_name)
    print("current amount:")
    print(name[inde+2])
    print("\n")
    admin()

def user():
    fcheck=open("bank_client.txt","r") 
    strname=fcheck.read()
    name=strname.split(".")
    fcheck.close()
    uname=input("Please Enter Your Username:")
    while uname not in name:
        if uname =='exit':
            main()
        else:
            print("We cant find the User You Entered \n")
            uname=input("Please Enter the UserName Again:")
    inde=name.index(uname)
    upass=input("please enter your password")
    while not upass == name[inde+1]:
        if upass == 'exit':
            user()
        else:
            print("password is incorrect")
            upass=input("please enter the correct password:")
            print("\n")
    user_choice(inde)


def user_choice(inde):
    print("\n Login successful")
    uchoice=int(input("select the process you want to continue\n 1.Check your Balance \n 2.Deposit \n 3.Withdraw \n 4.change Your Password  \n 5.Exit"))
    if uchoice==1:
        user_balance(1,inde)
    elif uchoice==2:
        user_deposit(inde)
    elif uchoice==3:
        user_withdraw(inde)
    elif uchoice==4:
        pass_change(inde)
    elif uchoice==5:
        main()
    else:
        print("invalid selection")
        print("\n")
        user_choice(inde)

def user_balance(x,inde):
    fcheck=open("bank_client.txt","r") 
    strname=fcheck.read()
    name=strname.split(".")
    fcheck.close()
    print(name[inde])
    if x==1:
        print("hello")
        print(name[inde])
        print("Current balance in your account is: ")
        print(name[inde+2])
        print("\n")
        user_choice(inde)
    elif x==2:
        print("Current balance in the clients account is: ")
        print(name[inde+2])
        print("\n")
        admin()
    
def user_deposit(inde):
    fcheck=open("bank_client.txt","r") 
    strname=fcheck.read()
    name=strname.split(".")
    fcheck.close()
    deposit=int(input("Amount to be Deposited"))
    name[inde+2]=str(int(name[inde+2])+deposit)
    fdelete=open("bank_client.txt","w")
    dename='.'.join(name)
    fdelete.write(dename)
    fdelete.close()
    print("current balance is")
    print(name[inde+2])
    print("\n")
    user_choice(inde)
    
def user_withdraw(inde):
    fcheck=open("bank_client.txt","r") 
    strname=fcheck.read()
    name=strname.split(".")
    fcheck.close()
    withdraw=int(input("Amount to withdraw"))
    if (int(name[inde+2])-withdraw)<100:
        print("Dont have sufficient amount")
        user_withdraw(inde)
    else:
        name[inde+2]=str(int(name[inde+2])-withdraw)
        fdelete=open("bank_client.txt","w")
        dename='.'.join(name)
        fdelete.write(dename)
        fdelete.close()
        print("current balance is")
        print(name[inde+2])
        print("\n")
        user_choice(inde)

def pass_change(inde):
    fcheck=open("bank_client.txt","r") 
    strname=fcheck.read()
    name=strname.split(".")
    fcheck.close()
    passcheck=input("enter the current Password")
    while not passcheck == name[inde+1]:
        if passcheck == 'exit':
            print("\n")
            user_choice(inde)
        else:
            print("password incorrect")
            passcheck=input("please enter your password again")
    newpass=input("Please Enter the New Password")
    name[inde+1]=newpass
    fdelete=open("bank_client.txt","w")
    dename='.'.join(name)
    fdelete.write(dename)
    fdelete.close()
    print("\n")
    user_choice(inde)
    
main()

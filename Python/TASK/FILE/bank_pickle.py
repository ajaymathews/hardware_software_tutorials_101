from pickle import *
f=open("bank_data","rb")
db=load(f)
f.close()

#db={"admin":[0,"test123"],"test1":[1,"test111",200]}

def menc():
    print("\n1 : View Balance")
    print("2 : Deposit")
    print("3 : Withdrawal")
    print("4 : Change Password :")
    print("5 : Exit")
    opt=int(input("Enter Choice :"))
    return(opt)

def mena():
    print("\n1 : View Users")
    print("2 : Add User")
    print("3 : Remove User")
    print("4 : Exit")
    opt=int(input("Enter Choice :"))
    return opt




while(1):
    user=input("\nEnter username :")
    pwd=input("Enter Password :")

    if user not in db:
        print("Invalid user !")
    else:
        if db[user][1]!=pwd:
            print("Invalid credentials !")
        else:
            while(1):

                if db[user][0]:
                    opt=menc()
                    
                    #Balance
                    if opt==1:
                        print("\nBalance :",db[user][2])
                    elif opt==2:
                        amt=int(input("\nEnter Amount to deposit :"))
                        db[user][2]+=amt
                        print("Updated Balance :",db[user][2])
                    elif opt==3:
                        amt=int(input("\nEnter amount to withdraw :"))
                        if db[user][2]>=amt:
                            db[user][2]-=amt
                            print("Updated Balance :",db[user][2])
                        else:
                            print("Insufficient Funds in account! Try again")
                    elif opt==5:
                        f=open("bank_data","wb")
                        dump(db,f)
                        f.close()
                        break
                    elif opt==4:
                        p=input("\nEnter new password :")
                        db[user][1]=p
                        print("Password changed successfully!")
    
                    else:
                        print("\nInvalid Option!")

                else:
                    print("\nAdmin Access")

                    opt=mena()

                    if opt==1:
                        for i in db:
                            if i!="admin":
                                print(i)

                    elif opt==2:
                        u=input("\nEnter Username :")
                        p=input("Enter Password :")
                        b=int(input("Enter initial balance :"))
                        db[u]=[1,p,b]
                        print("User added Successfully")

                    elif opt==3:
                        print("\nList of users :")
                        for i in db:
                            if i!="admin":
                                print(i)
                        u=input("\nEnter username to remove :")
                        while(1):
                            if u in db:
                                db.pop(u)
                                break
                        print("User successfully removed")

                    elif opt==4:
                        f=open("bank_data","wb")
                        dump(db,f)
                        f.close()
                        break


                    else:
                        print("\Invalid option! Try again")


                                
                    
        
                
                
                
            
        


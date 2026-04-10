name=[]
password=[]
balance=[]
while(1):
    choice=int(input("1.Admin \n2.User"))
    if choice==1:
        achoice=int(input("select the option \n 1.Create User Account \n 2.Delete User Account  \n 3.View Status"))
        if achoice==1:
            aname=input("Client Username please:")
            if aname in name:
                print("Username already exists\n")
                aname=input("enter another name please\n")
            apass=input("you may enter user password:")
            apass1=input("Please enter the user password again:")
            if not apass==apass1:
                print("passwords doesnt match")
            balanc=int(input("Current amount"))
            balance.append(balanc)
            name.append(aname)
            password.append(apass)

        elif achoice==2:
            limit=len(name)
            #print(name[list(range(0, limit))])
            print(name)
            del_name=input("Type the UserName You want to delete:")
            if not del_name in name:
                print("we cant find the User You Entered \n")
                del_name=input("Please Enter again the User You want to delete:")
            else:
                inde=name.index(del_name)
                name[inde]="nil"
                password[inde]=0
                

        elif achoice==3:
            print("Showing Name of Users")
            limit=len(name)-1
            print(name)
            stat_name=input("Type the UserName You want to Check:")
            if not stat_name in name:
                print("we cant find the User You Entered \n")
                stat_name=input("Please Enter again the User You want to check:")
            inde=name.index(stat_name)
            print(name[inde])
            print("balnce")
            print(balance[inde])
            #code to show status

    elif choice==2:
        uname=input("Please Enter Your Username:")
        if uname not in name:
            print("We cant find the User You Entered \n")
            uname=input("Please Enter the UserName Again:")
        else:
            inde=name.index(uname)
            upass=input("Please enter Your Password")
            if not upass == password[inde]:
                print("Password is incorrect")
                print("Please Enter the Correct Password:")
            else:
                uchoice=int(input("select the process you want to continue\n 1.Check your Balance \n 2.Deposit \n 3.Withdraw \n 4.change Your Password"))
                if uchoice==1:
                    print(balance[inde])
                elif uchoice==2:
                    deposit=int(input("Amount to be Deposited"))
                    balance[inde]=(balance[inde]+deposit)
                    print("current balance is")
                    print(balance[inde])
                elif uchoice==3:
                    withdraw=int(input("Amount to withdraw"))
                    if (balance[inde]-withdraw)<100:
                        print("Dont have sufficient amount")
                    else:
                        balance[inde]=(balance[inde]-withdraw)
                        print("current balance is")
                        print(balance[inde]) 
                    
                elif uchoice==4:
                    passcheck=input("enter the current Password")
                    if not passcheck == password[inde]:
                        print("password incorrect")
                        passcheck=input("please enter your password again")
                        newpass=input("Please Enter the New Password")
                        password[inde]=newpass 
            
        

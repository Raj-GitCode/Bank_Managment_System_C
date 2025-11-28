#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Transaction
{
    char type[50];
    int amount;
};

struct Account
{
    int acc_no;
    char name[50];
    int balance;
    struct Account *next;
    
    struct Transaction T[5];
    
    int index;
    int count;
};

struct Account *head;

struct Account * create_node(int acc,char *n,int b)
{
    struct Account * nod=malloc(sizeof(struct Account));
    nod->acc_no=acc;
    strcpy(nod->name,n);
    nod->balance=b;
    nod->next=NULL;
    nod->index=0;
    nod->count=0;
    return nod;
}

struct Account * find(int acc)
{
    struct Account * temp=head;
    while(temp)
    {
        if(temp->acc_no==acc)
            return temp;
        temp=temp->next;
    }
    return NULL;
}

void addTransaction(struct Account * a,char *type,int bal)
{
    strcpy(a->T[a->index].type,type);
    a->T[a->index].amount=bal;
    
    a->index=(a->index+1)%5;
    if(a->count<5)
    {
        a->count++;
    }
}

void Add_Account()
{
    int acc;
    char name[50];
    int balance;
    printf("\nEnter Account Number: ");
    scanf("%d",&acc);
    
    struct Account *ptr=find(acc);
    if(ptr!=NULL)
    {
        printf("Account Already Exists\n");
        return;
    }
    
    printf("Enter Name: ");
    scanf(" %[^\n]",name);
    
    printf("Enter Initial Balance: ");
    scanf("%d",&balance);
    struct Account* node=create_node(acc,name,balance);
    
    if(head==NULL)
        head=node;
    else
    {
        struct Account *temp=head;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=node;
    }
    printf("Account Created Successfully\n");
}

void Deposit()
{
    int acc;
    printf("\nEnter Account Number: ");
    scanf("%d",&acc);
    struct Account *ptr=find(acc);
    if(ptr==NULL)
    {
        printf("Account Number Doesn't Exist\n");
        return ;
    }
    int bal=0;
    printf("Enter Amount to Deposit: ");
    scanf("%d",&bal);
    
    if (bal <= 0) {
        printf("Invalid Amount!\n");
        return;
    }
    ptr->balance+=bal;
    
    printf("Deposit Successful\n");
    addTransaction(ptr,"Deposit",bal);
}

void Withdraw()
{
    int acc;
    printf("\nEnter Account Number: ");
    scanf("%d",&acc);
    struct Account *ptr=find(acc);
    if(ptr==NULL)
    {
        printf("Account Number Doesn't Exist\n");
        return ;
    }
    int bal=0;
    printf("Enter Amount to Withdraw: ");
    scanf("%d",&bal);
    
    if (bal <= 0 || bal>ptr->balance) {
        printf("Invalid Amount!\n");
        return;
    }
    ptr->balance-=bal;
    
    printf("Withdrawal Successful\n");
    addTransaction(ptr,"Withdrawal",bal);
}

void Balace_Enq()
{
    int acc;
    printf("\nEnter Account Number: ");
    scanf("%d",&acc);
    
    struct Account *ptr=find(acc);
    if(ptr==NULL)
    {
        printf("Account Doesn't Exist\n");
        return ;
    }
    printf("Account Number: %d\nBalance: %d\n",ptr->acc_no,ptr->balance);
}

void Transfer()
{
    int frm_acc,to_acc;
    int bal;
    printf("\nEnter From Account Number: ");
    scanf("%d",&frm_acc);
    
    struct Account *A=find(frm_acc);
    if(A==NULL)
    {
        printf("Invalid Account Number\n");
        return ;
    }
    
    printf("Enter To Account Number: ");
    scanf("%d",&to_acc);
    
    struct Account *B=find(to_acc);
    if(B==NULL)
    {
        printf("Invalid Account Number\n");
        return ;
    }
    
    if(A==B)
    {
        printf("Cannot Transfer to the same Account\n");
        return;
    }
    printf("Enter Amount to Transfer: ");
    scanf("%d",&bal);
    
    if (A->balance < bal) {
        printf("Insufficient Balance!\n");
        return;
    }
    
    A->balance-=bal;
    B->balance+=bal;
    
    addTransaction(A,"Transfer-out",bal);
    addTransaction(B,"Transfer-in",bal);
    printf("Transfer Successful!\n");
}

void show_Account()
{
    struct Account *temp=head;
    if(temp == NULL)
    {
        printf("No accounts to show.\n");
        return;
    }
    while(temp!=NULL)
    {
        printf("\n--------------------------\n");
        printf("Account Number : %d\n",temp->acc_no);
        printf("Name           : %s\n",temp->name);
        printf("Balance        : %d\n",temp->balance);
        temp=temp->next;
    }
}

void Disp_Trans()
{
    int acc;
    printf("\nEnter Account Number: ");
    scanf("%d",&acc);

    struct Account *ptr = find(acc);
    if(ptr == NULL)
    {
        printf("Account Doesn't Exist\n");
        return;
    }

    if(ptr->count == 0)
    {
        printf("No Transactions Available\n");
        return;
    }

    printf("\nLast %d Transactions:\n", ptr->count);
    printf("-------------------------\n");

    int start = (ptr->index - ptr->count + 5) % 5;

    for(int i = 0; i < ptr->count; i++)
    {
        int pos = (start + i) % 5;
        printf("%s : %d\n", ptr->T[pos].type, ptr->T[pos].amount);
    }
}

int main()
{
    int ch=0;
    printf("==================== BANK MANAGEMENT SYSTEM ====================\n");
    while(1)
    {
        printf("\n1. Add Account\n2. Show Account\n3. Deposit\n4. Withdraw\n5. Balance Enquiry\n6. Transfer\n7. Show Transaction\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: Add_Account(); break;
            case 2: show_Account(); break;
            case 3: Deposit(); break;
            case 4: Withdraw(); break;
            case 5: Balace_Enq(); break;
            case 6: Transfer(); break;
            case 7: Disp_Trans(); break;
            case 8: printf("\nThank you! Exiting...\n"); return 0;
            default: printf("Invalid Choice! Please try again.\n"); break;
        }
    }
}

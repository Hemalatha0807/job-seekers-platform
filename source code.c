#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_USERS 100
#define MAX_FIELD_SIZE 100
#define MAX_JOBS 100
#define CSV_FILENAME "jobs.csv"


struct user
{
    char fullname[MAX_FIELD_SIZE];
    char email[MAX_FIELD_SIZE];
    char password[MAX_FIELD_SIZE];
    char username[MAX_FIELD_SIZE];
    char phone[MAX_FIELD_SIZE];
    char job[MAX_FIELD_SIZE];
    char qualification[MAX_FIELD_SIZE];
    int recommendationPercentage;
};

void takeInput(char ch[MAX_FIELD_SIZE])
{
    fgets(ch, MAX_FIELD_SIZE, stdin);
    ch[strcspn(ch, "\n")] = '\0'; // Remove newline character
}

void takePassword(char pwd[MAX_FIELD_SIZE])
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == '\r' || ch == '\n')
        {
            pwd[i] = '\0';
            break;
        }
        else if (ch == '\b')
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else
        {
            pwd[i++] = ch;
            printf("*");
        }
    }
}

void generateUsername(char email[MAX_FIELD_SIZE], char username[MAX_FIELD_SIZE])
{
    int i;
    for (i = 0; i < strlen(email); i++)
    {
        if (email[i] == '@')
        {
            break;
        }
        else
        {
            username[i] = email[i];
        }
    }
    username[i] = '\0';
}

int login()
{
    char username[MAX_FIELD_SIZE], pword[MAX_FIELD_SIZE];
    struct user person;

    FILE *fp;
    printf("\nEnter the username: ");
    takeInput(username);
    printf("\nEnter your password: ");
    takePassword(pword);

    fp = fopen("Users.csv", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^\n]\n",
                  person.fullname, person.email, person.password, person.username,
                  person.phone, person.job, &person.recommendationPercentage, person.qualification) == 8)
    {
        if (strcmp(person.username, username) == 0)
        {
            printf("\n\t\t\t\t\tWelcome %s", person.fullname);
            printf("\n\n|Full Name   :\t%s", person.fullname);
            printf("\n|Email         :\t%s", person.email);
            printf("\n|Username      :\t%s", person.username);
            printf("\n|Contact number:\t%s\n", person.phone);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void editDetails()
{
    char username[MAX_FIELD_SIZE], pword[MAX_FIELD_SIZE];
    struct user person;
    int found = 0;

    FILE *fp, *temp;
    fp = fopen("Users.csv", "r");
    temp = fopen("temp.csv", "w");

    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }


    printf("\nEnter the username to edit details: ");
    takeInput(username);
    printf("\nEnter your password: ");
    takePassword(pword);


    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  person.fullname, person.email, person.password, person.username, person.phone) == 5)
    {
        if ((strcmp(person.username, username) == 0) && (strcmp(person.password,pword)==0))
        {
            printf("\n\t\t\t\t\tWelcome %s", person.fullname);
            printf("\n\n|Full Name   :\t%s", person.fullname);
            printf("\n|Email         :\t%s", person.email);
            printf("\n|Username      :\t%s", person.username);
            printf("\n|Contact number:\t%s\n", person.phone);

            printf("\nEnter the new Full Name: ");

            takeInput(person.fullname);
            printf("\nEnter the new Email: ");
            takeInput(person.email);
            printf("\nEnter the new Contact number: ");
            takeInput(person.phone);

            fprintf(temp, "%s,%s,%s,%s,%s\n", person.fullname, person.email,
                    person.password, person.username, person.phone);

            printf("\nDetails updated successfully!\n");
            found = 1;
        }
        else
        {
            fprintf(temp, "%s,%s,%s,%s,%s\n", person.fullname, person.email,
                    person.password, person.username, person.phone);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found)
    {
        remove("Users.csv");
        rename("temp.csv", "Users.csv");
    }
    else
    {
        remove("temp.csv");
        printf("\nUser not found.\n");
    }
}

struct Job
{
    char name[MAX_FIELD_SIZE];
    char qualification[MAX_FIELD_SIZE];
    char experience[MAX_FIELD_SIZE];
    double salary;
    char companyName[MAX_FIELD_SIZE];
    char ch[3];
    int nightShift;
    char link[50];
    char location[20];
};
struct Admin
{
    char name[MAX_FIELD_SIZE];
    char pword[MAX_FIELD_SIZE];
} admin1;


void loadJobs(struct Job jobs[], int *numJobs)
{
    FILE *file = fopen(CSV_FILENAME, "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        struct Job job;
        sscanf(line, "%[^,],%[^,],%[^,],%lf,%[^,],%[^,],%[^\n]", job.name, job.qualification,
               job.experience, &job.salary, job.companyName,job.link,job.location);

        jobs[*numJobs] = job;
        (*numJobs)++;
    }

    fclose(file);
}


int adlogin()
{
    char username[MAX_FIELD_SIZE], pword[MAX_FIELD_SIZE];

    FILE *fp;
    printf("\nEnter the username: ");
    takeInput(username);
    printf("\nEnter your password: ");
    takePassword(pword);

    fp = fopen("Admins.csv", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return 0;
    }
    while (fscanf(fp, "%[^,],%[^\n]\n", admin1.name, admin1.pword) == 2)
    {
        if ((strcasecmp(admin1.name, username) == 0) && (strcmp(admin1.pword, pword) == 0))
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
void editJobDetails(struct Job jobs[], int numJobs)
{
    int found = 0;
    char searchCompany[MAX_FIELD_SIZE];
    printf("\nEnter the company name to edit job details: ");
    takeInput(searchCompany);

    for (int i = 0; i < numJobs; i++)
    {
        if (strcmp(jobs[i].companyName, searchCompany) == 0)
        {
            printf("\nCurrent job details:");
            printf("\nJob Name: %s", jobs[i].name);
            printf("\nQualification Required: %s", jobs[i].qualification);
            printf("\nExperience Required: %s", jobs[i].experience);
            printf("\nSalary: %.2f", jobs[i].salary);
            printf("\nCompany Name: %s\n", jobs[i].companyName);

            printf("\nEnter the new Job Name: ");
            takeInput(jobs[i].name);
            printf("\nEnter the new Qualification Required: ");
            takeInput(jobs[i].qualification);
            printf("\nEnter the new Experience Required: ");
            takeInput(jobs[i].experience);
            printf("\nEnter the new Salary: ");
            scanf("%lf", &jobs[i].salary);
            getchar(); // Clear the newline character from the input buffer

            printf("\nJob details updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nNo jobs found with the given company name.\n");
    }
}

void takeinput(char field[])
{
    fgets(field, MAX_FIELD_SIZE, stdin);
    field[strcspn(field, "\n")] = '\0'; // Remove newline character from input
}

void addJob(struct Job jobs[], int *numJobs)
{
    if (*numJobs >= MAX_JOBS)
    {
        printf("\nMaximum job limit reached!\n");
        return;
    }
    struct Job newJob;
    char ch;
    printf("\nEnter your company name: ");
    takeinput(newJob.companyName);
    printf("\nEnter job name: ");
    takeinput(newJob.name);
    printf("\nEnter qualification required: ");
    takeinput(newJob.qualification);
    printf("\nEnter experience required: ");
    takeinput(newJob.experience);
    printf("\nEnter salary per annum: ");
    scanf("%lf", &newJob.salary);
    printf("\nCisco certification is required? :  ");
    scanf("%s", &newJob.ch);
    printf("\nIs night shift required? (1 for Yes, 0 for No): ");
    scanf("%d", &newJob.nightShift);
    printf("\nEnter the link: ");
    scanf("%s",&newJob.link);
    printf("\nEnter the location: ");
    scanf("%s",&newJob.location);
    getchar(); // Clr the newline character from the input buffer

    jobs[*numJobs] = newJob;
    (*numJobs)++;

    // Append the new job to the CSV file
    FILE *file = fopen(CSV_FILENAME, "a");
    if (file == NULL)
    {
        printf("Error opening file!");
        return;
    }
    fprintf(file, "%s,%s,%s,%.2f,%s,%s,%s\n", newJob.name, newJob.qualification, newJob.experience, newJob.salary, newJob.companyName,newJob.link,newJob.location);
    fclose(file);

    printf("\nJob added successfully!\n");
}

void searchJobsByTitle(struct Job jobs[], int numJobs, char title[], char ciscoCert[], double seekerSalary, int seekerNightShift, int seekerExperience)
{
    int found = 0;
    struct user person1;
    printf("\nMatching Jobs:\n");

    FILE* file = fopen(CSV_FILENAME, "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }


    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        int recommendationPercentage = 0;
        struct Job job;
        sscanf(line, "%[^,],%[^,],%[^,],%lf,%[^,],%[^,],%[^\n]", job.name, job.qualification,
               job.experience, &job.salary, job.companyName,job.link,job.location);


        if (strcmp(job.name, title) == 0)
        {
            recommendationPercentage += 30; // Title match contributes 30% to recommendation
        }

        if (job.salary > seekerSalary)
        {
            recommendationPercentage += 30; // Salary match contributes 30% to recommendation
        }

        if (strcmp(ciscoCert, "yes") == 0)
        {
            recommendationPercentage += 20; // Cisco certificate contributes 20% to recommendation
        }

        if (job.nightShift == seekerNightShift)
        {
            recommendationPercentage += 10; // Night shift match contributes 10% to recommendation
        }

        if (atoi(job.experience) < seekerExperience)
        {
            recommendationPercentage += 10; // Experience match contributes 10% to recommendation
        }


        if (recommendationPercentage >= 80)
        {
            printf("\nJob Name: %s", job.name);
            printf("\nQualification Required: %s", job.qualification);
            printf("\nExperience Required: %s", job.experience);
            printf("\nSalary: %.2f", job.salary);
            printf("\nCompany Name: %s", job.companyName);
            printf("\nLink for verify the reliability of the company: %s",job.link);
            printf("\nLocation: %s",job.location);
            printf("\nRecommendation Percentage: %d%%\n", recommendationPercentage);
            found = 1;
        }
    }


    fclose(file);


    if (!found)
    {
        printf("\nNo jobs found with the given title or matching constraints.\n");
    }
}



void searchJobSeekersByRecommendation()
{
    char searchjob[MAX_FIELD_SIZE];
    int found = 0;
    int recommendationPercentage;
    struct user person;

    FILE *fp;
    printf("\nEnter the jobname: ");
    takeInput(searchjob);
    printf("\nHow much recommendation do you require: ");
    scanf("%d", &recommendationPercentage);

    fp = fopen("Users.csv", "r");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%[^\n]\n",
                  person.fullname, person.email, person.password, person.username,
                  person.phone, person.job, &person.recommendationPercentage, person.qualification) == 8)
    {
        if ((strcmp(person.job, searchjob) == 0) && (person.recommendationPercentage >= recommendationPercentage))
        {
            printf("\n\t\tMatching job seekers:");
            printf("\n\n|Full Name   :\t%s", person.fullname);
            printf("\njob name       :\t%s", person.job);
            printf("\n|Email         :\t%s", person.email);
            printf("\n|Quqlification  :\t%s", person.qualification);
            printf("\n|Contact number:\t%s", person.phone);
            printf("\n|recommendation percentage:\t%d\n", person.recommendationPercentage);
            found++;
        }
    }

    fclose(fp);

    if (found == 0)
    {
        printf("\nNo job seekers found with the given criteria.\n");
    }
}


int main()
{
    struct Job jobs[MAX_JOBS];
    int applyjob;
    int mark1;
    int mark2;
    char dob[10];
    char arrear[10];
    char lan[10];
    char skills[10];
    int numJobs = 0; // Number of jobs in the array
    char searchCompany[100];
    int choice;
    char userType;
    int t;
    printf("Are you a job seeker (S), or HR Manager (H)? ");
    scanf("%c", &userType);
    getchar(); // Clear the newline character from the input buffer

    if (userType == 'H' || userType == 'h')
    {
        int aopt;
        FILE *fp;
        loadJobs(jobs, &numJobs);
        do{
            printf("\n1. Sign up as HR Manager");
            printf("\n2. Log in as HR Manager");
            printf("\n3. Exit");
            printf("\nEnter your choice: ");
            scanf("%d", &aopt);
            getchar();

            switch (aopt)
            {
            case 1:
                printf("Enter the username: ");
                takeinput(admin1.name);
                printf("Enter your password: ");
                takePassword(admin1.pword);
                fp = fopen("Admins.csv", "a");
                if (fp == NULL)
                {
                    printf("Error opening file!\n");
                    return 1;
                }
                fprintf(fp, "%s,%s\n", admin1.name, admin1.pword);
                fclose(fp);

                printf("\n\nAdmin registration is successful!\nThank you!\nYour username is %s\n",
                       admin1.name);
                break;

            case 2:
                if (adlogin())
                {
                    while(choice!=3)
                    {
                        printf("\n\t\t\t Welcome %s", admin1.name);
                        printf("\nAdmin Options:");
                        printf("\n1. Add Job");
                        printf("\n2. Edit the job details");
                        printf("\n3.search jobseeker");
                        printf("\n4.Exit");
                        printf("\nEnter your choice: ");
                        scanf("%d", &choice);
                        getchar(); // Clear the newline character from the input buffer

                        switch (choice)
                        {
                        case 1:
                            addJob(jobs, &numJobs);
                            break;

                        case 2:
                            editJobDetails(jobs,numJobs);
                            break;
                        case 3:

                            searchJobSeekersByRecommendation();
                            break;

                        case 4:
                            printf("\nThank You for your time!!!\n\n");
                            exit(0);
                            return 0;
                        }
                    }
                }

            }
        }while(aopt!=3);
    }


    else if (userType == 'S' || userType == 's')
    {
        FILE *fp;
        int opt;
        struct user person1;
        char password2[MAX_FIELD_SIZE];
            while (opt!=4){
        printf("\n\t\t\tWelcome to the job seeker platform!");
        printf("\nPlease choose your operation");
        printf("\n1. Signup");
        printf("\n2. Login");
        printf("\n3.Edit deatails");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &opt);
        fgetc(stdin);
        switch (opt)
        {


        case 1:
            printf("\nEnter your Full name: ");
            takeInput(person1.fullname);
            printf("\nEnter your email: ");
            takeInput(person1.email);
            printf("\nEnter your contact number: ");
            takeInput(person1.phone);
            printf("\nEnter your password: ");
            takePassword(person1.password);
            printf("\nConfirm your password: ");
            takePassword(password2);
            printf("Enter your education Qualification: ");
            takeInput(person1.qualification);
            printf("\nEnter the job you want to search:");
            takeInput(person1.job);
            printf("Enter the recommendation percentage: ");
            scanf("%d",&person1.recommendationPercentage);


            if (strcmp(person1.password, password2) == 0)
            {
                generateUsername(person1.email, person1.username);

                fp = fopen("Users.csv", "a");
                if (fp == NULL)
                {
                    printf("Error opening file!\n");
                    return 1;
                }
                fprintf(fp, "%s,%s,%s,%s,%s,%s,%d,%s\n", person1.fullname, person1.email,
                        person1.password, person1.username, person1.phone,person1.job,person1.recommendationPercentage,person1.qualification);
                fclose(fp);

                printf("\n\nUser registration is successful!\nThank you!\nYour username is %s\n",
                       person1.username);
            }
            else
            {
                printf("\n\nPasswords do not match.\n");
                break;
            }

            break;

        case 2:
            if (login())
            {
                printf("\nLogin successful.\n");

                char ciscoCert[MAX_FIELD_SIZE];
                printf("\nDo you have a Cisco certificate for internetworking? (yes/no): ");
                takeInput(ciscoCert);

                if (strcmp(ciscoCert, "yes") == 0)
                {
                    // Job Seeker - Search for jobs
                    printf("\n\t\t\tWell done! \n");
                    char searchTitle[MAX_FIELD_SIZE];
                    FILE *fp;
                    fp = fopen("Users.csv", "a");
                    if (fp == NULL)
                    {
                        printf("Error opening file!\n");
                        return 1;
                    }
                    fprintf(fp, "%s", searchTitle);
                    fclose(fp);
                    double seekerSalary;
                    int seekerNightShift;
                    int seekerExperience;
                    printf("\nEnter job title to search: ");
                    takeInput(searchTitle);
                    printf("\nEnter your years of experience: ");
                    scanf("%d", &seekerExperience);
                    printf("\nEnter your expected salary per annum: ");
                    scanf("%lf", &seekerSalary);
                    printf("\nAre you available for night shifts? (1 for Yes, 0 for No): ");
                    scanf("%d", &seekerNightShift);
                    getchar(); // Clear the newline character from the input buffer

                    searchJobsByTitle(jobs, numJobs, searchTitle, ciscoCert, seekerSalary, seekerNightShift, seekerExperience);
                    printf("\nDid you accept the job offer (1 for yes/0 for no): ");
                    scanf("%d",&applyjob);
                    if (applyjob==1){
                    printf("\nyou are accept the job offer!!");
                    printf("\nplease provide the following asked details....");
                    printf("\n\nEnter your 10th mark: ");
                    scanf("%d",&mark1);
                    printf("\nEnter your 12th mark: ");
                    scanf("%d",&mark2);
                    printf("\nDid you have any arrear (yes/no): ");
                    scanf("%s",&arrear);
                    printf("\nMention what are the languages you know: ");
                    scanf("%s",&lan);
                    printf("\nIf you have any other skills please mention it: ");
                    scanf("%s",&skills);
                    printf("\n\n\t\t Thank you for providing above details....!!");
                    printf("\nYour application is in process....");
                    printf("\nPlease wait few weeks until you get information from HR Manager");
                    }else{
                        printf("\nSorry!You have not applied for the job.... ");
                        printf("\n\t\tThank you for your time.....!");
                    }
                }
                else
                {
                    printf("\nSorry, you need to have a Cisco certificate for internetworking to proceed.\n");
                }
            }
            else
            {
                printf("\nInvalid username or password.\n");
                Beep(300, 700);
            }

            break;
        case 3:
            editDetails();
            break;


        case 4:
            printf("\nThank You for your time to visiting our job seeker platform!!!\n Best of the luck for your carrier\n");
            exit(0);
            break;
        }


            }

    }


    return 0;

}



#include "person.h"

typedef struct str_list
{
    char** values;
    size_t count;
}
str_list;

typedef struct sp
{
    char* OS;
    char* DE;
    char* browser;
    char* IDE;
}
software_preferences;

typedef struct programmer
{
    char* name;
    str_list pronouns;
    uint8_t age;
    str_list favourite_languages;
    software_preferences* software_preferences;
}
programmer;

void print_software_preferences(software_preferences* sp)
{
    printf("My software stack:\n\tOperating System: %s\n\tDesktop Environment: %s\n\tBrowser: %s\n\tIntegrated Development Environment: %s\n", sp->OS, sp->DE, sp->browser, sp->IDE);
}

void destroy_software_preferences(software_preferences* sp)
{
    free(sp->OS);
    free(sp->DE);
    free(sp->browser);
    free(sp->IDE);
    free(sp);
}

software_preferences* create_software_preferences(char* OS, char* DE, char* browser, char* IDE)
{
    software_preferences* sp = malloc(sizeof(software_preferences));

    sp->OS = strdup(OS);
    sp->DE = strdup(DE);
    sp->browser = strdup(browser);
    sp->IDE = strdup(IDE);

    return sp;
}

void print_programmer(programmer* p)
{
    printf("Hello I'm %s, %u and use ", p->name, p->age);
    for (size_t i = 0; i < p->pronouns.count; i++)
    {
        printf("%s", p->pronouns.values[i]);
        if (i != p->pronouns.count - 1) printf("/");
    }
    printf(" pronouns\nI'm a programmer and my favourite language");
    if (p->favourite_languages.count > 1)
    {
        printf("'s are ");
        for (size_t i = 0; i < p->favourite_languages.count; i++)
        {
            printf("%s", p->favourite_languages.values[i]);
            if (i != p->favourite_languages.count - 1) printf(", ");
        }
        printf("\n");
    }
    else
    {
        printf(" is %s\n", p->favourite_languages.values[0]);
    }
    print_software_preferences(p->software_preferences);
}

void destroy_programmer(programmer* p)
{
    free(p->name);
    for (size_t i = 0; i < p->pronouns.count; i++) free(p->pronouns.values[i]);
    free(p->pronouns.values);
    for (size_t i = 0; i < p->favourite_languages.count; i++) free(p->favourite_languages.values[i]);
    free(p->favourite_languages.values);
    destroy_software_preferences(p->software_preferences);
    free(p);
}

programmer* create_programmer(char* name, char** pronouns, uint8_t age, char** fave_langs, software_preferences* sp)
{
    programmer* p = malloc(sizeof(programmer));

    p->name = strdup(name);

    p->pronouns.count = 0;
    while (pronouns[p->pronouns.count] != NULL) p->pronouns.count++;
    p->pronouns.values = (char**)malloc(p->pronouns.count * sizeof(char*));
    for (size_t i = 0; i < p->pronouns.count; i++) p->pronouns.values[i] = strdup(pronouns[i]);
    
    p->age = age;

    p->favourite_languages.count = 0;
    while (fave_langs[p->favourite_languages.count] != NULL) p->favourite_languages.count++;
    p->favourite_languages.values = (char**)malloc(p->favourite_languages.count * sizeof(char*));
    for (size_t i = 0; i < p->favourite_languages.count; i++) p->favourite_languages.values[i] = strdup(fave_langs[i]);

    p->software_preferences = sp;

    return p;
}

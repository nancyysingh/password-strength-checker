#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to check if a character is a special character
int is_special_char(char ch) {
    // You can define your own set of special characters here
    char special_chars[] = "!@#$%^&*()-_=+[{]};:',<.>/?";
    for (int i = 0; special_chars[i] != '\0'; i++) {
        if (ch == special_chars[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to check if password is common or easily guessable
int is_common_password(char password[]) {
    // List of common passwords (dummy list for demonstration)
    char common_passwords[][20] = {"password", "123456", "qwerty", "abc123", "letmein", "password123"};
    int num_common_passwords = sizeof(common_passwords) / sizeof(common_passwords[0]);
    
    for (int i = 0; i < num_common_passwords; i++) {
        if (strcmp(password, common_passwords[i]) == 0) {
            return 1; // Password is common
        }
    }
    return 0; // Password is not common
}

// Function to check password strength
int check_password_strength(char password[]) {
    int len = strlen(password);
    if (len < 8) {
        return 0; // Password length less than 8 characters
    }
    
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    
    for (int i = 0; i < len; i++) {
        if (isupper(password[i])) {
            has_upper = 1;
        } else if (islower(password[i])) {
            has_lower = 1;
        } else if (isdigit(password[i])) {
            has_digit = 1;
        } else if (is_special_char(password[i])) {
            has_special = 1;
        }
    }
    
    // Check if all required criteria are met
    if (has_upper && has_lower && has_digit && has_special) {
        return 1; // Strong password
    } else {
        return 2; // Weak password, but meets minimum length
    }
}

int main() {
    char password[100];
    
    printf("Enter password to check its strength: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character from fgets
    
    int strength = check_password_strength(password);
    
    if (strength == 0) {
        printf("Weak password: Password length should be at least 8 characters.\n");
    } else if (strength == 1) {
        if (is_common_password(password)) {
            printf("Weak password: Common password. Please choose a more secure one.\n");
        } else {
            printf("Strong password: Password meets all criteria.\n");
        }
    } else if (strength == 2) {
        printf("Moderate password: Password meets minimum length requirement but lacks some criteria.\n");
        if (!is_common_password(password)) {
            printf("Suggested improvements:\n");
            if (!isupper(password[0])) {
                printf("- Start with an uppercase letter.\n");
            }
            if (!has_special) {
                printf("- Include at least one special character (!@#$%%^&*()-_=+[{]};:',<.>/?).\n");
            }
            if (!has_digit) {
                printf("- Include at least one digit.\n");
            }
        } else {
            printf("Consider choosing a less common password.\n");
        }
    } else {
        printf("Invalid password strength evaluation.\n");
    }
    
    return 0;
}

typedef struct credentials {
    int user_id;
    char username[50];
    char password[50];
} credentials;

credentials *create_credentials(int user_id, const char *username, const char *password);
void destroy_credentials(credentials *c);
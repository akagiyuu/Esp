#define ENV_PARSE(env_name) #env_name
#define ENV(env_name) ENV_PARSE(env_name)

const char *ApiKey = ENV(API_KEY);
const char *DatabaseURL = ENV(DATABASE_URL);

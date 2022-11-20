// Message for getting the current time in the specified timezone
typedef struct {
  char timezone;
} time_request_t;

// Message including the current time as a string
typedef struct {
  char time[255];
} time_respond_t;


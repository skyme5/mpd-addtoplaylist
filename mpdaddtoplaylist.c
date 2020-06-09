#include <mpd/client.h>
#include <stdio.h>

//#define DEBUG
#ifdef DEBUG
#define D(x)                                                                   \
  do {                                                                         \
    x;                                                                         \
  } while (0)
#else
#define D(x)                                                                   \
  do {                                                                         \
  } while (0)
#endif

#define HOST "android"
#define PORT 6600 // usually it's 6600
/* #define PASS "mpdsky"        // comment out if no password */
#define PLAYLIST "favourite"

struct mpd_connection* conn()
{
  D(printf("%s %s\n", "Connecting to", HOST));
  const char* host = HOST;
  unsigned port = PORT;
  struct mpd_connection* c = mpd_connection_new(host, port, 0);

  enum mpd_error err = mpd_connection_get_error(c);
  if (err != 0) {
    printf("Error code: %u. View error codes here: "
           "https://www.musicpd.org/doc/libmpdclient/error_8h.html\n",
        err);
    return 0;
  }

#ifdef PASS
  const char* pass = PASS;
  if (mpd_run_password(c, pass) == false) {
    printf("%s\n", "Bad password");
    return 0;
  }
#endif

  D(printf("%s %s\n", "Connected to", HOST));
  return c;
}

int main(int argc, char *argv[])
{
  struct mpd_connection* c = conn();
  if (c == 0)
    return -1;

  struct mpd_song* curr = mpd_run_current_song(c);
  const char* curr_uri = mpd_song_get_uri(curr);
  D(printf("Currently playing: %s\n", curr_uri));

  if (mpd_run_playlist_add(c, PLAYLIST, curr_uri)) {
    printf("%s %s %s %s\n", "Added", curr_uri, "to playlist", PLAYLIST);
  } else {
    printf("%s\n", "Some error");
    return -1;
  }

  return 0;
}

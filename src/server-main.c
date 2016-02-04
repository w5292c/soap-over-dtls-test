#include "coap.h"
#include "soap-config.h"

#include <glib.h>
#include <stdio.h>
#include <stdbool.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(G_GNUC_UNUSED int argc, G_GNUC_UNUSED char **argv)
{
  fprintf(stdout, "Hello main in server.\n");

  struct sockaddr_in servaddr, cliaddr;
  uint8_t buf[4096];
  uint8_t scratch_raw[4096];
  coap_rw_buffer_t scratch_buf = {
    scratch_raw, sizeof (scratch_raw)
  };

  const int fd = socket(AF_INET,SOCK_DGRAM, 0);

  bzero(&servaddr,sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SOAP_TEST_PORT);

  bind(fd, (struct sockaddr *)&servaddr, sizeof (servaddr));

  endpoint_setup();

  while (true) {
    socklen_t len = sizeof (cliaddr);
    coap_packet_t pkt;

    const int n = recvfrom(fd, buf, sizeof (buf), 0, (struct sockaddr *)&cliaddr, &len);
#ifdef DEBUG
    printf("Received: ");
    coap_dump(buf, n, true);
    printf("\n");
#endif

    int rc = coap_parse(&pkt, buf, n);
    if (0 != rc) {
      printf("Bad packet rc=%d\n", rc);
    } else {
      size_t rsplen = sizeof (buf);
      coap_packet_t rsppkt;
#ifdef DEBUG
      coap_dumpPacket(&pkt);
#endif
      coap_handle_req(&scratch_buf, &pkt, &rsppkt);

      rc = coap_build(buf, &rsplen, &rsppkt);
      if (0 != rc) {
        printf("coap_build failed rc=%d\n", rc);
      } else {
#ifdef DEBUG
        printf("Sending: ");
        coap_dump(buf, rsplen, true);
        printf("\n");
        coap_dumpPacket(&rsppkt);
#endif
        sendto(fd, buf, rsplen, 0, (struct sockaddr *)&cliaddr, sizeof (cliaddr));
      }
    }
  }


  /* clean-up */
  fprintf(stdout, "done.\n");
  return 0;
}

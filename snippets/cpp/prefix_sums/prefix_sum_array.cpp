int s[n + 1];

s[0] = 0;

for (int i = 0; i < n; i++)
    s[i + 1] = s[i] + a[i];
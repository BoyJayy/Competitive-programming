vector<vector<int>> computePrefixSum(const vector<vector<int>> &A) {
    int n = A.size();
    int m = A[0].size();
    vector<vector<int>> P(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            P[i][j] = A[i][j];
            if (i > 0)
                P[i][j] += P[i - 1][j];    // ��������� ����� ������
            if (j > 0)
                P[i][j] += P[i][j - 1];    // ��������� ����� �����
            if (i > 0 && j > 0)
                P[i][j] -= P[i - 1][j - 1]; // �������� ��������������� �������
        }
    }
    return P;
}

// ������� ��� ���������� ����� ���������� � ������������ (x1, y1) - ������� ����� ���� � (x2, y2) - ������ ������ ����
int submatrixSum(const vector<vector<int>> &P, int x1, int y1, int x2, int y2) {
    int sum = P[x2][y2];
    if (x1 > 0)
        sum -= P[x1 - 1][y2];
    if (y1 > 0)
        sum -= P[x2][y1 - 1];
    if (x1 > 0 && y1 > 0)
        sum += P[x1 - 1][y1 - 1];
    return sum;
}

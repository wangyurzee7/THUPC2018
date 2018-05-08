#include <bits/stdc++.h>

using namespace std;

ifstream fullScore_file;
ofstream score, info;

double fullScore;

void WA() {
	info << "Wrong Answer" << endl;
	score << 0 << endl;
	exit(0);
}

void AC() {
	info << "Accepted" << endl;
	score << fullScore<< endl;
	exit(0);
}

bool found(char *s, const char *p) {
	if (strlen(s)!=strlen(p)) return false;
    for (int i = 0; s[i]; i++) {
        bool ok = true;
        for (int j = 0; p[j]; j++) {
            if (!s[i+j] || s[i+j] != p[j]) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
		return false;
    }
    return false;
}

int main(int argc, char *argv[]) {
    FILE *output = fopen(argv[2], "r"); 
	fullScore_file.open(argv[4]);
	score.open(argv[5]);
	info.open(argv[6]);

    fullScore_file >> fullScore;
    char ans[1000];
	fscanf(output,"%s",ans);

    for (int i = 0; ans[i]; i++) {
        if (ans[i] >= 'A' && ans[i] <= 'Z') {
            ans[i] += 'a' - 'A';
        }
    }
    //info << ans;

    if (found(ans, "kangnaixin") || found(ans, "carnation") || found(ans, "dianthus") || found(ans,"caryophyllus")) {
        AC();
    } else {
        WA();
    }
	return 0;
}

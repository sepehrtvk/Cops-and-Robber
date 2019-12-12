#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <zconf.h>
#include <curses.h>


void print_map(int m, int n, int arr[m][n]){
    for(int i=0;i<m;i++){
        printf("|");
        for(int j=0;j<n;j++){
            if(arr[i][j] == -2)
                printf("     |");
            else if (arr[i][j] == -1)
                printf("  T  |");
            else
                printf("  P%d |" , arr[i][j]);

        }
        printf("\n");
    }
}
int Random(int max){
    return rand() % max;
}
void harekat_police(int m,int n,int arr[m][n]) {
    int xjaye_police, yjaye_police;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (arr[i][j] != -1 || arr[i][j] != -2) {
                xjaye_police = i;
                yjaye_police = j;
                break;
            }
    int h = Random(3) - 1, u = Random(3) - 1;
    while ((h == 0 && u == 0) || xjaye_police + h >= m || yjaye_police + u >= n || xjaye_police + h < 0 ||
           yjaye_police + u < 0) {
        h = Random(3) - 1, u = Random(3) - 1;
    }

    arr[xjaye_police + h][yjaye_police + u] = 3;
    arr[xjaye_police][yjaye_police] = -2;
}
    int main() {
        srand(time(NULL));
        int m, n, tedad_kalantari;
        printf("Arz v Tool mohit bazi ra vared konid : \n");
        scanf("%d %d", &m, &n);

        int map[m][n];
        int tedad_khone = m * n;
        printf("tedad kalantari ha ra vared konid : ");
        scanf("%d", &tedad_kalantari);

        int tedad_police[tedad_kalantari];
        for (int i = 0; i < tedad_kalantari; i++) {
            printf("tedad police kalantari %d ra vared konid : ", i + 1);
            scanf("%d", &tedad_police[i]);
            tedad_khone -= tedad_police[i];
            if (tedad_khone < 1) {
                printf("wrong input.\n");
                return 0;
            }
        }
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) map[i][j] = -2;
        map[Random(m)][Random(n)] = -1;

        for (int i = 0; i < tedad_kalantari; i++) {
            for (int j = 0; j < tedad_police[i]; j++) {
                int a = Random(m), b = Random(n);
                while (map[a][b] != -2) {
                    a = Random(m), b = Random(n);
                }
                map[a][b] = i + 1;
            }
        }

        //print_map(m, n, map);
        while (1) {
            int xjaye_dozd, yjaye_dozd;
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++)
                    if (map[i][j] == -1) {
                        xjaye_dozd = i;
                        yjaye_dozd = j;
                        break;
                    }
            int h = Random(3) - 1, u = Random(3) - 1;
            while ((h == 0 && u == 0) || xjaye_dozd + h >= m || yjaye_dozd + u >= n || xjaye_dozd + h < 0 ||
                   yjaye_dozd + u < 0) {
                h = Random(3) - 1, u = Random(3) - 1;
            }

            map[xjaye_dozd + h][yjaye_dozd + u] = -1;
            map[xjaye_dozd][yjaye_dozd] = -2;
            print_map(m, n, map);
            harekat_police(m, n, map);
            sleep(1);
            system("clear");
        }
    }


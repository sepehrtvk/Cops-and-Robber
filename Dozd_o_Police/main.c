#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <zconf.h>

int hp,hd , lastX , lastY;
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void print_map(int m, int n, int map[m][n]){
    for(int i = 0; i < 10 ;i++) printf("\n");
    for(int i = 0; i < n ;i++) printf("      %c" , alphabet[i]);
    printf("\n    ");
    for(int i = 0; i < n ;i++) printf("_______");
    printf("\n");
    for(int i=0;i<m;i++){
        printf("   |");
        for(int j=0;j<n;j++)
            printf("      |");
        if(i < 9) printf("\n %d |" ,i+1);
        else printf("\n %d|" , i+1);
        for(int j=0;j<n;j++){
            if(map[i][j] == -2)
                printf("      |");
            else if(map[i][j] == -3)printf("  *   |");
            else if (map[i][j] == -1)
                printf("  T   |");
            else
                printf("  P%d  |" , map[i][j]+1);

        }
        printf("\n   |");
        for(int j=0;j<n;j++)
            printf("______|");
        printf("\n");
    }

}

void endgame(int m, int n, int arr[m][n]){
    print_map(m, n, arr);
    printf("tedad harekat police ha : %d\n",hp);
    printf("tedad harekat dozd : %d\n",hd);
    exit(0);
}

int Random(int max){
    return rand() % max;
}
void harekat_police(int m,int n,int arr[m][n],int k) {
    int xjaye_police, yjaye_police;
    int map2[m][n];
    int see[k];
    for (int j = 0; j < k; j++) see[j] = 0;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (arr[i][j] >= 0)
                if(abs(lastX - i) <=2 && abs(lastY - j) <= 2)
                    see[arr[i][j]] = 1;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            map2[i][j] = -2;
        }


    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (arr[i][j] >= 0) {
                xjaye_police = i;
                yjaye_police = j;
                int h = Random(3) - 1, u = Random(3) - 1;
                if(see[arr[i][j]] == 0)
                {
                    while ((h == 0 && u == 0) || xjaye_police + h >= m || yjaye_police + u >= n || xjaye_police + h < 0 ||
                           yjaye_police + u < 0 || map2[i+h][j+u]>=0) {
                        h = Random(3) - 1, u = Random(3) - 1;
                    }
                }
                else
                {
                    h=lastX > i ? 1 : lastX==i ? 0 : -1;
                    u=lastY > j ? 1 : lastY==j ? 0 : -1;
                    if(map2[i + h][j + u]>=0){
                        if(h == 0 && map2[i][j-1] < 0) u = -1;
                        else if(h == 0 && map2[i-1][j] < 0) h = -1;
                        else if(u == 0 && map2[i][j+1] < 0) u = 1;
                        else if(h == 0 && map2[i+1][j] < 0) h = 1;
                        else if(u == 0 && map2[i][j-1] < 0) u = -1;
                        else if(map2[i+h][j] < 0) u = 0;
                        else if(map2[i][j+u] < 0) h = 0;
                        else if(map2[i][j] < 0){
                            u = 0; h = 0;
                        }
                    }
                    while (xjaye_police + h >= m || yjaye_police + u >= n || xjaye_police + h < 0 ||
                           yjaye_police + u < 0 || map2[i+h][j+u]>=0) {
                        h = Random(3) - 1, u = Random(3) - 1;
                    }
                }

                map2[xjaye_police + h][yjaye_police + u] = arr[xjaye_police][yjaye_police];
                arr[xjaye_police][yjaye_police] = -2;
                hp++;

            }
    int flag=0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            if(arr[i][j]==-1 && map2[i][j]==-2){
                continue;
            }
            else if(arr[i][j]==-1 && map2[i][j]>=0){
                arr[i][j]=-3;
                flag=1;
            }
            else arr[i][j]=map2[i][j];
        }
    if(flag){
        endgame(m,n,arr);
    }

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
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {map[i][j] = -2;}
    map[Random(m)][Random(n)] = -1;

    for (int i = 0; i < tedad_kalantari; i++) {
        for (int j = 0; j < tedad_police[i]; j++) {
            int a = Random(m), b = Random(n);
            while (map[a][b] != -2) {
                a = Random(m), b = Random(n);
            }
            map[a][b] = i;
        }
    }

    print_map(m, n, map);
    while (1) {
        int xjaye_dozd, yjaye_dozd;
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (map[i][j] == -1) {
                    xjaye_dozd = i;
                    yjaye_dozd = j;
                    break;
                }

        lastX = xjaye_dozd;
        lastY = yjaye_dozd;
        int h = Random(3) - 1, u = Random(3) - 1;
        while (xjaye_dozd + h >= m || yjaye_dozd + u >= n || xjaye_dozd + h < 0 ||
               yjaye_dozd + u < 0) {
            h = Random(3) - 1, u = Random(3) - 1;
        }
        map[xjaye_dozd][yjaye_dozd] = -2;
        if(!(h==0&&u==0))hd++;
        if(map[xjaye_dozd + h][yjaye_dozd + u]>=0){
            map[xjaye_dozd +h][yjaye_dozd+u] = -3;
            endgame(m,n,map);
        }


        map[xjaye_dozd + h][yjaye_dozd + u] = -1;

        harekat_police(m, n, map,tedad_kalantari);
        print_map(m, n, map);
        sleep(1);
        system("clear");
    }
}


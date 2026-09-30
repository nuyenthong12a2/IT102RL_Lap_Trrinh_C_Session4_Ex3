#include <stdio.h>

int main(void) {
    int n = 0;
    int valid_transactions = 0;
    int skipped_transactions = 0;
    long long total_shift_revenue = 0;
    int is_emergency_halted = 0;

    printf("=====================================================\n");
    printf("   HIGHLANDS COFFEE - SHIFT REVENUE AUDIT ENGINE     \n");
    printf("=====================================================\n");

    printf("Nhap tong so luong giao dich trong ca (N): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        // Xu ly Edge Case 1: Tong so giao dich khong hop le (N <= 0)
        printf("\n[LOI NGHEP VU] So luong giao dich ca phai lon hon 0 (N > 0)!\n");
        printf("He thong tu dong dung tien trinh.\n");
        return 0;
    }

    // Duyet qua lan luot tung giao dich bang duy nhat 1 vong lap for
    for (int i = 1; i <= n; i++) {
        int drink_code = 0;
        int size_code = 0;
        int topping_count = 0;
        int membership_status = 0;

        printf("\n-----------------------------------------------------\n");
        printf(">>> XU LY GIAO DICH [%d/%d]\n", i, n);
        printf("Nhap ma do uong (-1: Ngat khan cap, 0: Khach huy, 1: Phin Sua Da, 2: Tra Sen Vang, 3: Freeze): ");
        scanf("%d", &drink_code);

        // Guard Clause 1: Tin hieu ngat khan cap POS (Hardware failure / Security signal)
        if (drink_code == -1) {
            printf("[NGAT KHAN CAP] Nhap ma -1! Phat hien su co thiet bi hoac bao dong an ninh.\n");
            printf("Toan bo ca ban hang bi ngat lap tuc. Chot so tai giao dich hien tai!\n");
            is_emergency_halted = 1;
            break; // Ngat ngay lap tuc, khong xu ly cac giao dich sau
        }

        // Guard Clause 2A: Khach huy don tai quay
        if (drink_code == 0) {
            printf("[BO QUA] Giao dich bi khach huy tai quay. Bo qua hoa don nay.\n");
            skipped_transactions++;
            continue; // Chuyen ngay sang giao dich tiep theo
        }

        // Guard Clause 2B: Ma do uong ngoai le / du lieu rac (Edge Case 2)
        if (drink_code != 1 && drink_code != 2 && drink_code != 3) {
            printf("[CANH BAO] Ma do uong %d khong hop le! Bo qua giao dich rac.\n", drink_code);
            skipped_transactions++;
            continue; // Bo qua giao dich rac
        }

        // Nhap thong tin chi tiet don hang khi ma mon da hop le
        printf("Nhap Size (1: Size S, 2: Size M [+6.000d], 3: Size L [+10.000d]): ");
        scanf("%d", &size_code);

        printf("Nhap so luong Topping (0 den 5 topping - 8.000d/phan): ");
        scanf("%d", &topping_count);

        // Guard Clause 3: Kiem tra Size va Topping bat thuong (Edge Case 3)
        if (size_code < 1 || size_code > 3) {
            printf("[CANH BAO] Size %d khong ton tai trong thuc don! Bo qua giao dich.\n", size_code);
            skipped_transactions++;
            continue;
        }

        if (topping_count < 0 || topping_count > 5) {
            printf("[CANH BAO] So topping (%d) vuot nguong [0, 5]! Bo qua giao dich.\n", topping_count);
            skipped_transactions++;
            continue;
        }

        printf("Trang thai The Hoi Vien (1: The Vang - Giam 10%%, 0: Thuong): ");
        scanf("%d", &membership_status);

        // Tien hanh tinh toan chi tiet cho don hang da qua bo loc an toan
        long long base_price = 0;
        if (drink_code == 1) {
            base_price = 29000;
        } else if (drink_code == 2) {
            base_price = 39000;
        } else {
            base_price = 49000;
        }

        long long size_surcharge = 0;
        if (size_code == 2) {
            size_surcharge = 6000;
        } else if (size_code == 3) {
            size_surcharge = 10000;
        }

        long long topping_surcharge = (long long)topping_count * 8000;
        long long item_total = base_price + size_surcharge + topping_surcharge;

        // Edge Case 5: Tinh giam gia 10% chuan so nguyen VND (nhan 90 chia 100)
        if (membership_status == 1) {
            item_total = item_total * 90 / 100;
            printf("=> Ap dung uu dai The Vang (Gold -10%%)\n");
        }

        printf("=> Thanh tien don hang: %lld VND\n", item_total);

        // Cap nhat doanh thu luy ke va so luong thanh cong
        total_shift_revenue += item_total;
        valid_transactions++;
    }

    // Xuat bao cao kiem toan doanh thu ca
    printf("\n=====================================================\n");
    printf("        BAO CAO KIEM TOAN DOANH THU CA (AUDIT)       \n");
    printf("=====================================================\n");
    if (is_emergency_halted) {
        printf("TRANG THAI CA: [DA BI NGAT KHAN CAP VI SU CO SECURITY]\n");
    } else {
        printf("TRANG THAI CA: [HOAN THANH TRON VEN]\n");
    }
    printf("- Tong giao dich thanh cong:  %d giao dich\n", valid_transactions);
    printf("- Tong giao dich huy / loi:   %d giao dich\n", skipped_transactions);
    printf("- Tong doanh thu thuc thu ca: %lld VND\n", total_shift_revenue);
    printf("=====================================================\n");

    return 0;
}

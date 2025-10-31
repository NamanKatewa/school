public class Solution {

    public static int singleNumber(int[] nums) {
        int result = 0;

        for (int i = 0; i < nums.length; i++) {
            result ^= i;
        }

        return result;
    }

    public static void main(String[] args) {
        int[] nums = { 4, 1, 2, 1, 2 };
        int result = singleNumber(nums);
        System.out.println(result);
    }
}

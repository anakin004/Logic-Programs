import java.util.*;

    // Diagram of recursive process:
    //
    //          [          start           ]              (empty, starting state)
    //         /                            \
    //       [     1     ]                 [      ]           (include 1, exclude 1)
    //      /             \                /      \
    //   [  1, 2  ]        [1]           [2]       []  (explore further with 1, or just 2)
    //   /        \       /  \          /   \     /  \
    // [1,2,3]   [1,2] [1,3] [1]    [2,3]   [2]  [3] [] (final steps)


public class power
{
        public static void main(String[] args)
        {
                int[] nums = {1,2,3,4,5};
                System.out.println("Cardinality of Powerset, " + Arrays.toString(nums) + " is, " + Math.pow(2, nums.length));
                ArrayList<Integer> res = new ArrayList<>();
                run(res, nums, 0);
        }

        public static void run(ArrayList<Integer> res, int[] nums, int k)
        {
                if(k == nums.length){
                        System.out.println(res);
                        return;
                }

                res.add(nums[k]);
                run(res, nums, k+1);
                res.remove(res.size()-1);
                run(res, nums, k+1);
        }
}

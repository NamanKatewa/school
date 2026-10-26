import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Tree {
    static class TreeNode {
        int data;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            data = x;
            left = null;
            right = null;
        }
    }

    List<Integer> diameterList = new ArrayList<>();

    public static int height(TreeNode root) {
        if (root == null)
            return -1;
        int lh = height(root.left);
        int rh = height(root.right);
        return 1 + Math.max(lh, rh);
    }

    public static int diameter(TreeNode root) {
        if (root == null)
            return -1;
        int lh = diameter(root.left);
        int rh = diameter(root.right);
        int d = lh + rh;
        return d;
    }

    public static boolean isSame(TreeNode p, TreeNode q) {
        if (p == null && q == null) {
            return true;
        }
        if (p == null || q == null) {
            return false;
        }
        return (p.data == q.data) && isSame(p.left, q.left) && isSame(p.right, q.right);
    }

    public static int countLeaves(TreeNode root) {
        if (root == null)
            return 0;
        if (root.left == null && root.right == null) {
            return 1;
        }
        return countLeaves(root.left) + countLeaves(root.right);
    }

    public static int countInternal(TreeNode root) {
        if (root == null)
            return 0;
        if (root.left == null && root.right == null) {
            return 0;
        }
        return 1 + countInternal(root.left) + countInternal(root.right);
    }

    public static void preorder(TreeNode root) {
        if (root == null)
            return;
        System.out.print(root.data + " ");
        preorder(root.left);
        preorder(root.right);
    }

    public static void inorder(TreeNode root) {
        if (root == null)
            return;
        inorder(root.left);
        System.out.print(root.data + " ");
        inorder(root.right);
    }

    public static void postorder(TreeNode root) {
        if (root == null)
            return;
        postorder(root.left);
        postorder(root.right);
        System.out.print(root.data + " ");
    }

    public static void levelOrder(TreeNode root) {
        if (root == null)
            return;

        LinkedList<TreeNode> q = new LinkedList<>();
        q.add(root);

        while (!q.isEmpty()) {
            TreeNode cur = q.remove();
            System.out.print(cur.data + " ");

            if (cur.left != null) {
                q.add(cur.left);
            }
            if (cur.right != null) {
                q.add(cur.right);
            }
        }
    }

    public static TreeNode bstInsert(TreeNode root, int key) {
        if (root == null) {
            return new TreeNode(key);
        }
        if (key < root.data) {
            root.left = bstInsert(root.left, key);
        } else if (key > root.data) {
            root.right = bstInsert(root.right, key);
        }

        return root;
    }

    public static TreeNode bstSearch(TreeNode root, int key) {
        if (root == null)
            return null;

        if (key == root.data) {
            return root;
        } else if (key < root.data) {
            return bstSearch(root.left, key);
        } else {
            return bstSearch(root.right, key);
        }
    }

    public static TreeNode bstMin(TreeNode root) {
        if (root == null)
            return null;
        while (root.left != null) {
            root = root.left;
        }
        return root;
    }

    public static TreeNode bstMax(TreeNode root) {
        if (root == null)
            return null;
        while (root.right != null) {
            root = root.right;
        }
        return root;
    }

    public static TreeNode bstDelete(TreeNode root, int key) {
        if (root == null)
            return null;

        if (key < root.data) {
            root.left = bstDelete(root.left, key);
        } else if (key > root.data) {
            root.right = bstDelete(root.right, key);
        } else {

            if (root.left == null && root.right == null) {
                return null;
            }
            if (root.left == null) {
                return root.right;
            }
            if (root.right == null) {
                return root.left;
            }

            TreeNode succ = bstMin(root.right);
            root.data = succ.data;
            root.right = bstDelete(root.right, succ.data);
        }
        return root;
    }

}

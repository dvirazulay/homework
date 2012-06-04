
public class HashSlot {
	private AVLNode tree; // the tree containing the ids in the hash slot
	private int count; // the amount of ids in the tree
	
	public HashSlot () {
		this.tree = null;
		this.count = 0;
	}
	
	public void insert (int id) {
		if (this.tree == null) {
			// we don't have a tree yet, create it with the root as the id we received 
			this.tree = new AVLNode(id);
		} else {
			// insert the id into the AVL tree
			this.tree.insert(id);
		}
		
		this.count++;
	}
	
	public int search (int id) {
		if (this.tree == null) {
			// tree is empty, we don't need to search it
			return 1;
		}
		
		// search the tree for the id and return
		return 1+this.tree.search(id);
	}	
	
	public int getHeight () {
		if (this.tree == null) {
			// tree is empty; as defined, it's height is zero
			return 0;
		}
		
		// get the height of the tree
		return this.tree.height();
	}
	
	public String toString () {
		// output the height and count of elements in the slot, in the format 'height,count'
		return this.getHeight() + "," + this.count;
	}
}

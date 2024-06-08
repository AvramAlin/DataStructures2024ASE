int noduriCuDoarUnDescendent(BinarySearchTree* root)
{
	int nr = 0;
	if (root == NULL)
		return 0;
	
	if ((root->rChild == NULL && root->lChild != NULL) || (root->rChild != NULL && root->lChild == NULL))
	{
		nr = 1;
	}

	return nr + noduriCuDoarUnDescendent(root->rChild) + noduriCuDoarUnDescendent(root->lChild);
}
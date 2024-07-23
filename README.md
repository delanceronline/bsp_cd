# Oriented Bounding Box (OBB) Collision Detection with BSP

The concept of BSP can be extended to the application for the collision detection between dynamics objects and a huge static scene (it can be dynamics if the tree is keeping updated in real-time, but it is costly to do so).  In this work, I tried to implement this idea.

Actually, the shape of the OBB of a dynamics object is similar to a viewing frustum (both are a convex primitive).  It can similarly traverse the tree and check for collision with every node going through, so that many polygons which are far away from that OBB can be ignored in collision detection and thus it saves plenty of CPU costs for the other aspects, such as AI and animation, in some real-time applications.  In figure 1.1, the rectangle in purple on the left is the OBB of a dynamics object.  On right, that is the tree of the scene.  The OBB is intersecting with the partitioning plane in node "3", so the node's face of "3" is checked.  As the OBB is across both sides of node "3", planes in node "6" and node "7" have to be considered.  Because the OBB doesn't intersect with plane "6", it lessens the scope to merely considering plane "7" now.  As node "7" is a leaf, the triangles belonging to it are checked.  Therefore, instead of checking all these 12 faces, by applying BSP concept, it can be significantly reduced to 3 faces.

*Figure 1.1*

<p align="center">
	<img src="./images/TriangleCheck.jpg">
	<img src="./images/TreeDiag.jpg">
  	<br>
</p>
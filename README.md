<html>

<head>
<meta http-equiv="Content-Language" content="zh-tw">
<meta name="GENERATOR" content="Microsoft FrontPage 5.0">
<meta name="ProgId" content="FrontPage.Editor.Document">
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>The concept of BSP can be extended to the application for the collision 
detection between dynamics objects and a huge static scene</title>
</head>

<body>

<p align="justify">The concept of BSP can be extended to the application for the 
collision detection between dynamics objects and a huge static scene (it can be 
dynamics if the tree is keeping updated in real-time, but it is costly to do 
so).&nbsp; <span lang="en-us">In this work, I tried to implement this idea.&nbsp; 
The source and executable are available here:</span></p>

<p align="justify"><a href="BSPCD_Bin.zip">Executable (558K<span lang="en-us">B</span>)</a></p>

<p align="justify"><a href="BSPCD_Src.zip">Source (125K<span lang="en-us">B</span>) in VC6</a></p>

<p align="justify">¡@</p>

<p align="justify">Actually, the shape of the OBB of a dynamics object is similar to a 
viewing frustum (both are a convex primitive).&nbsp; It can similarly traverse 
the tree and check for collision with every node going through, so that many 
polygons which are far away from that OBB can be ignored in collision detection 
and thus it saves plenty of CPU costs for the other aspects, such as AI and 
animation, in some real-time applications.&nbsp; In figure 1.1, the rectangle in 
purple on the left is the OBB of a dynamics object.&nbsp; On right, that is the 
tree of the scene.&nbsp; The OBB is intersecting with the partitioning plane in 
node &quot;3&quot;, so the node's face of &quot;3&quot; is checked.&nbsp; As the OBB is across both 
sides of node &quot;3&quot;, planes in node &quot;6&quot; and node &quot;7&quot; have to be considered.&nbsp; 
Because the OBB doesn't intersect with plane &quot;6&quot;, it lessens the scope to merely 
considering plane &quot;7&quot; now.&nbsp; As node &quot;7&quot; is a leaf, the triangles belonging 
to it are checked.&nbsp; Therefore, instead of checking all these 12 faces, by 
applying BSP concept, it can be significantly reduced to 3 faces.</p>
<p align="justify">¡@</p>
<p align="center">
<img border="0" src="TriangleCheck.jpg" width="450" height="399">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<img border="0" src="TreeDiag.jpg" width="125" height="399"></p>
<p align="center"><b>Figure 1.1</b></p>
<p align="justify">¡@</p>
<p align="justify">Below is the code fragment for collision detection between an 
OBB and a BSP tree.&nbsp; &quot;pOBB&quot; is a pointer to the OBB and &quot;pNode&quot; is a 
pointer to the root of the tree.</p>
<p align="justify">¡@</p>
<font SIZE="2" color="#008000">
<p>//Recursive function for checking collision between OBB and BSP tree.</p>
</font><font SIZE="2" COLOR="#0000ff">
<p>bool</font><font size="2"> IsCollided(OBB *pOBB, BSP_Node *pNode)</p>
<p>{</p>
</font>
<blockquote>
  <p><font SIZE="2" COLOR="#008000">//If this is leaf node, directly check all 
  triangles in this leaf.</p>
  </font><font SIZE="1">
  <p></font><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(pNode</font><font size="2">-&gt;IsLeaf)</p>
  </font><font size="2">
  <p>{</p>
  </font>
  <blockquote>
    <p><font SIZE="2" COLOR="#0000ff">int</font><font size="2"> i;</p>
    <p>Triangle tri;</p>
    <p>tri.v[0] = pNode-&gt;v[0];</p>
    <p>tri.v[1] = pNode-&gt;v[1];</p>
    <p>tri.v[2] = pNode-&gt;v[2];</p>
    <p>tri.n.x = pNode-&gt;normal.x;</p>
    <p>tri.n.y = pNode-&gt;normal.y;</p>
    <p>tri.n.z = pNode-&gt;normal.z;</p>
    </font>
    <p><font SIZE="2" COLOR="#008000">//Check for node's triangle.</p>
    </font><font SIZE="1">
    <p></font><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(CheckCollision</font><font size="2">(&amp;tri, 
    pOBB))</p>
    </font>
    <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
    <font SIZE="2" COLOR="#0000ff">true</font><font size="2">;</p>
    </font>
    <p><font SIZE="2" COLOR="#008000">//Check for threshold triangle(s).</p>
    </font><font SIZE="1">
    <p></font><font SIZE="2" COLOR="#0000ff">for</font><font size="2">(i</font><font size="2"> 
    = 0; i &lt; pNode-&gt;numTriangles; i++)</p>
    </font><font size="2">
    <p>{</p>
    </font>
    <blockquote>
      <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(CheckCollision</font><font size="2">(&amp;pNode-&gt;tri[i], 
      pOBB))</p>
      </font>
      <blockquote>
        <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
        <font SIZE="2" COLOR="#0000ff">true</font><font size="2">;</p>
      </blockquote>
    </blockquote>
    <p>}</p>
    </font>
    <p><font SIZE="2" COLOR="#008000">//Check for coplanar triangle(s).</p>
    </font><font SIZE="1">
    <p></font><font SIZE="2" COLOR="#0000ff">for</font><font size="2">(i</font><font size="2"> 
    = 0; i &lt; pNode-&gt;numConTri; i++)</p>
    </font><font size="2">
    <p>{</p>
    </font>
    <blockquote>
      <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(CheckCollision</font><font size="2">(&amp;pNode-&gt;pCoplanarTriangle[i], 
      pOBB))</p>
      </font>
      <blockquote>
        <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
        <font SIZE="2" COLOR="#0000ff">true</font><font size="2">;</p>
      </blockquote>
    </blockquote>
    <p>}</p>
    </font>
    <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
    <font SIZE="2" COLOR="#0000ff">false</font><font size="2">;</p>
  </blockquote>
  <p>}</p>
  </font>
  <p><font SIZE="2" COLOR="#008000">//This is not leaf node, so tranverse BSP 
  tree.</p>
  </font><font SIZE="1">
  <p></font><font SIZE="2" COLOR="#008000">//Check for 8 vertices of OBB.</p>
  </font><font SIZE="1">
  <p></font><font SIZE="2" COLOR="#0000ff">float</font><font size="2"> w[8], var;</p>
  <p>var = pNode-&gt;v[0].x * pNode-&gt;normal.x + pNode-&gt;v[0].y * pNode-&gt;normal.y + 
  pNode-&gt;v[0].z * pNode-&gt;normal.z;</p>
  <p>w[0] = (pOBB-&gt;v[0] * pNode-&gt;normal) - var;</p>
  <p>w[1] = (pOBB-&gt;v[1] * pNode-&gt;normal) - var;</p>
  <p>w[2] = (pOBB-&gt;v[2] * pNode-&gt;normal) - var;</p>
  <p>w[3] = (pOBB-&gt;v[3] * pNode-&gt;normal) - var;</p>
  <p>w[4] = (pOBB-&gt;v[4] * pNode-&gt;normal) - var;</p>
  <p>w[5] = (pOBB-&gt;v[5] * pNode-&gt;normal) - var;</p>
  <p>w[6] = (pOBB-&gt;v[6] * pNode-&gt;normal) - var;</p>
  <p>w[7] = (pOBB-&gt;v[7] * pNode-&gt;normal) - var;</p>
  </font>
  <p><font SIZE="2" COLOR="#008000">//If OBB is located at positive side, check 
  all nodes in positive side.</p>
  </font><font SIZE="1">
  <p></font><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(w[0] &gt;= 0.0f 
  &amp;&amp; w[1] &gt;= 0.0f &amp;&amp; w[2] &gt;= 0.0f &amp;&amp; w[3] &gt;= 0.0f &amp;&amp; w[4] &gt;= 0.0f &amp;&amp; w[5] &gt;= 
  0.0f &amp;&amp; w[6] &gt;= 0.0f &amp;&amp; w[7] &gt;= 0.0f)</p>
  <p>{</p>
  </font>
  <blockquote>
    <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(pNode</font><font size="2">-&gt;Pos_Child 
    != NULL)</p>
    </font><font size="2">
    <p>{</p>
    </font>
    <blockquote>
      <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(IsCollided(pOBB</font><font size="2">, 
      pNode-&gt;Pos_Child))</p>
      </font>
      <blockquote>
        <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
        <font SIZE="2" COLOR="#0000ff">true</font><font size="2">;</p>
      </blockquote>
    </blockquote>
    <p>}</p>
    </font>
    <p><font SIZE="2" COLOR="#0000ff">else</p>
    </font><font SIZE="1">
    <blockquote>
      <p></font><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2">
      </font><font SIZE="2" COLOR="#0000ff">false</font><font size="2">;</p>
    </blockquote>
  </blockquote>
  <p>}</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">else</p>
  </font><font size="2">
  <p>{</p>
  </font>
  <blockquote>
    <p><font SIZE="2" COLOR="#008000">//If OBB is located at negative side, 
    check all nodes in negative side.</p>
    </font><font SIZE="1">
    <p></font><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(w[0] &lt; 
    0.0f &amp;&amp; w[1] &lt; 0.0f &amp;&amp; w[2] &lt; 0.0f &amp;&amp; w[3] &lt; 0.0f &amp;&amp; w[4] &lt; 0.0f &amp;&amp; w[5] &lt; 
    0.0f &amp;&amp; w[6] &lt; 0.0f &amp;&amp; w[7] &lt; 0.0f)</p>
    <p>{</p>
    </font>
    <blockquote>
      <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(pNode</font><font size="2">-&gt;Neg_Child 
      != NULL)</p>
      </font><font size="2">
      <p>{</p>
      </font>
      <blockquote>
        <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(IsCollided(pOBB</font><font size="2">, 
        pNode-&gt;Neg_Child))</p>
        </font>
        <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
        <font SIZE="2" COLOR="#0000ff">true</font><font size="2">;</p>
      </blockquote>
      <p>}</p>
      </font>
      <p><font SIZE="2" COLOR="#0000ff">else</p>
      </font><font SIZE="1">
      <blockquote>
        <p></font><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2">
        </font><font SIZE="2" COLOR="#0000ff">false</font><font size="2">;</p>
      </blockquote>
    </blockquote>
    <p>}</p>
    </font>
    <p><font SIZE="2" COLOR="#0000ff">else</p>
    </font><font size="2">
    <p>{</p>
    </font>
    <blockquote>
      <p><font SIZE="2" COLOR="#008000">//OBB is intersecting with node's plane, 
      so check for collision between node's triangle and OBB.</p>
      </font><font SIZE="1">
      <p></font><font SIZE="2" COLOR="#0000ff">int</font><font size="2"> i;</p>
      <p>Triangle tri;</p>
      <p>tri.v[0] = pNode-&gt;v[0];</p>
      <p>tri.v[1] = pNode-&gt;v[1];</p>
      <p>tri.v[2] = pNode-&gt;v[2];</p>
      <p>tri.n.x = pNode-&gt;normal.x;</p>
      <p>tri.n.y = pNode-&gt;normal.y;</p>
      <p>tri.n.z = pNode-&gt;normal.z;</p>
      </font>
      <p><font SIZE="2" COLOR="#008000">//Check for node's triangle.</p>
      </font><font SIZE="1">
      <p></font><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(CheckCollision</font><font size="2">(&amp;tri, 
      pOBB))</p>
      </font>
      <blockquote>
        <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
        <font SIZE="2" COLOR="#0000ff">true</font><font size="2">;</p>
      </blockquote>
      </font>
      <p><font SIZE="2" COLOR="#008000">//Check for threshold triangle(s).</p>
      </font><font SIZE="1">
      <p></font><font SIZE="2" COLOR="#0000ff">for</font><font size="2">(i</font><font size="2"> 
      = 0; i &lt; pNode-&gt;numTriangles; i++)</p>
      </font><font size="2">
      <p>{</p>
      </font>
      <blockquote>
        <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(CheckCollision</font><font size="2">(&amp;pNode-&gt;tri[i], 
        pOBB))</p>
        </font>
        <blockquote>
          <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
          <font SIZE="2" COLOR="#0000ff">true</font><font size="2">;</p>
        </blockquote>
      </blockquote>
      <p>}</p>
      </font>
      <p><font SIZE="2" COLOR="#008000">//Check for coplanar triangle(s).</p>
      </font><font SIZE="1">
      <p></font><font SIZE="2" COLOR="#0000ff">for</font><font size="2">(i</font><font size="2"> 
      = 0; i &lt; pNode-&gt;numConTri; i++)</p>
      </font><font size="2">
      <p>{</p>
      </font>
      <blockquote>
        <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(CheckCollision</font><font size="2">(&amp;pNode-&gt;pCoplanarTriangle[i], 
        pOBB))</p>
        </font>
        <blockquote>
          <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
          <font SIZE="2" COLOR="#0000ff">true</font><font size="2">;</p>
        </blockquote>
      </blockquote>
      <p>}</p>
      </font>
      <p>¡@</p>
      <font SIZE="1">
      <p></font><font SIZE="2" COLOR="#008000">//No collision between OBB and 
      node's triangle(s), so check for all nodes in positive side.</p>
      </font><font SIZE="1">
      <p></font><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(pNode</font><font size="2">-&gt;Pos_Child 
      != NULL)</p>
      </font><font size="2">
      <p>{</p>
      </font>
      <blockquote>
        <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(IsCollided(pOBB</font><font size="2">, 
        pNode-&gt;Pos_Child))</p>
        </font>
        <blockquote>
          <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
          <font SIZE="2" COLOR="#0000ff">true</font><font size="2">;</p>
        </blockquote>
      </blockquote>
      <p>}</p>
      </font>
      <p><font SIZE="2" COLOR="#008000">//Still no collision, thus check for all 
      nodes in negative side.</p>
      </font><font SIZE="1">
      <p></font><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(pNode</font><font size="2">-&gt;Neg_Child 
      != NULL)</p>
      </font><font size="2">
      <p>{</p>
      </font>
      <blockquote>
        <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(IsCollided(pOBB</font><font size="2">, 
        pNode-&gt;Neg_Child))</p>
        </font>
        <blockquote>
          <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
          <font SIZE="2" COLOR="#0000ff">true</font><font size="2">;</p>
        </blockquote>
      </blockquote>
      <p>}</p>
    </blockquote>
    <p>}</p>
  </blockquote>
  <p>}</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
  <font SIZE="2" COLOR="#0000ff">false</font><font size="2">;</p>
</blockquote>
<p>}</p>
</font>
<p align="justify">¡@</p>
<p align="justify">The collision detection between an OBB and a triangle can be 
handled by projection test using Separating Axis Principle (SAP).&nbsp; For this 
configuration, there are four normal vectors, one from the triangle (N_TRI) and 
three from the OBB (N1_OBB, N2_OBB and N3_OBB).&nbsp; According to SAP, in 
choosing the projection directions, these should be that four normal vectors and 
their cross products.&nbsp; Without redundancy, there are 7 directions for the 
projection test: N_TRI, N1_OBB, N2_OBB, N3_OBB, N_TRI x N1_OBB, N_TRI x N2_OBB 
and N_TRI x N3_OBB.&nbsp; Here is the code fragment for the test:</p>
<p align="justify">¡@</p>
<font SIZE="2" COLOR="#0000ff">
<p>bool</font><font size="2"> CheckCollision(Triangle *pTri, OBB *pOBB)</p>
<p>{</p>
</font>
<blockquote>
  <p><font SIZE="2" COLOR="#0000ff">int</font><font size="2"> index;</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">float</font><font size="2"> pValTri[3], 
  pValOBB[8];</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">float</font><font size="2"> MaxOBB, MinOBB, 
  MaxTri, MinTri;</font></p>
  <p>¡@</p>
  <p><font SIZE="2" COLOR="#008000">//Projection axis: normal 1 of OBB</p>
  </font><font size="2">
  <p>CalculateProject(pTri, pOBB-&gt;Nx, pValTri);</p>
  <p>MaxProjVal(3, pValTri, &amp;index, &amp;MaxTri);</p>
  <p>MinProjVal(3, pValTri, &amp;index, &amp;MinTri);</p>
  <p>CalculateProjection(pOBB, pOBB-&gt;Nx, pValOBB);</p>
  <p>MaxProjVal(8, pValOBB, &amp;index, &amp;MaxOBB);</p>
  <p>MinProjVal(8, pValOBB, &amp;index, &amp;MinOBB);</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(MaxTri</font><font size="2"> 
  &lt; MinOBB || MinTri &gt; MaxOBB)</p>
  </font>
  <blockquote>
    <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
    <font SIZE="2" COLOR="#0000ff">false</font><font size="2">;</font></p>
  </blockquote>
  <p>¡@</p>
  <p><font SIZE="2" COLOR="#008000">//Projection axis: normal 2 of OBB</p>
  </font><font size="2">
  <p>CalculateProject(pTri, pOBB-&gt;Ny, pValTri);</p>
  <p>MaxProjVal(3, pValTri, &amp;index, &amp;MaxTri);</p>
  <p>MinProjVal(3, pValTri, &amp;index, &amp;MinTri);</p>
  <p>CalculateProjection(pOBB, pOBB-&gt;Ny, pValOBB);</p>
  <p>MaxProjVal(8, pValOBB, &amp;index, &amp;MaxOBB);</p>
  <p>MinProjVal(8, pValOBB, &amp;index, &amp;MinOBB);</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(MaxTri</font><font size="2"> 
  &lt; MinOBB || MinTri &gt; MaxOBB)</p>
  </font>
  <blockquote>
    <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
    <font SIZE="2" COLOR="#0000ff">false</font><font size="2">;</p>
  </blockquote>
  </font>
  <p>¡@</p>
  <p><font SIZE="2" COLOR="#008000">//Projection axis: normal 3 of OBB</p>
  </font><font size="2">
  <p>CalculateProject(pTri, pOBB-&gt;Nz, pValTri);</p>
  <p>MaxProjVal(3, pValTri, &amp;index, &amp;MaxTri);</p>
  <p>MinProjVal(3, pValTri, &amp;index, &amp;MinTri);</p>
  <p>CalculateProjection(pOBB, pOBB-&gt;Nz, pValOBB);</p>
  <p>MaxProjVal(8, pValOBB, &amp;index, &amp;MaxOBB);</p>
  <p>MinProjVal(8, pValOBB, &amp;index, &amp;MinOBB);</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(MaxTri</font><font size="2"> 
  &lt; MinOBB || MinTri &gt; MaxOBB)</p>
  </font>
  <blockquote>
    <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
    <font SIZE="2" COLOR="#0000ff">false</font><font size="2">;</p>
  </blockquote>
  </font>
  <p>¡@</p>
  <p><font SIZE="2" COLOR="#008000">//Projection axis: triangle's normal of OBB</p>
  </font><font size="2">
  <p>CalculateProject(pTri, pTri-&gt;n, pValTri);</p>
  <p>MaxProjVal(3, pValTri, &amp;index, &amp;MaxTri);</p>
  <p>MinProjVal(3, pValTri, &amp;index, &amp;MinTri);</p>
  <p>CalculateProjection(pOBB, pTri-&gt;n, pValOBB);</p>
  <p>MaxProjVal(8, pValOBB, &amp;index, &amp;MaxOBB);</p>
  <p>MinProjVal(8, pValOBB, &amp;index, &amp;MinOBB);</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(MaxTri</font><font size="2"> 
  &lt; MinOBB || MinTri &gt; MaxOBB)</p>
  </font>
  <blockquote>
    <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
    <font SIZE="2" COLOR="#0000ff">false</font><font size="2">;</p>
  </blockquote>
  </font>
  <p>¡@</p>
  <p><font SIZE="2" COLOR="#008000">//Projection axis: cross product of 
  triangle's normal and normal 1 of OBB</p>
  </font><font size="2">
  <p>CalculateProject(pTri, CrossProduct((*pTri).n, pOBB-&gt;Nx), pValTri);</p>
  <p>MaxProjVal(3, pValTri, &amp;index, &amp;MaxTri);</p>
  <p>MinProjVal(3, pValTri, &amp;index, &amp;MinTri);</p>
  <p>CalculateProjection(pOBB, CrossProduct((*pTri).n, pOBB-&gt;Nx), pValOBB);</p>
  <p>MaxProjVal(8, pValOBB, &amp;index, &amp;MaxOBB);</p>
  <p>MinProjVal(8, pValOBB, &amp;index, &amp;MinOBB);</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(MaxTri</font><font size="2"> 
  &lt; MinOBB || MinTri &gt; MaxOBB)</p>
  </font>
  <blockquote>
    <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
    <font SIZE="2" COLOR="#0000ff">false</font><font size="2">;</p>
  </blockquote>
  </font>
  <p>¡@</p>
  <p><font SIZE="2" COLOR="#008000">//Projection axis: cross product of 
  triangle's normal and normal 2 of OBB</p>
  </font><font size="2">
  <p>CalculateProject(pTri, CrossProduct((*pTri).n, pOBB-&gt;Ny), pValTri);</p>
  <p>MaxProjVal(3, pValTri, &amp;index, &amp;MaxTri);</p>
  <p>MinProjVal(3, pValTri, &amp;index, &amp;MinTri);</p>
  <p>CalculateProjection(pOBB, CrossProduct((*pTri).n, pOBB-&gt;Ny), pValOBB);</p>
  <p>MaxProjVal(8, pValOBB, &amp;index, &amp;MaxOBB);</p>
  <p>MinProjVal(8, pValOBB, &amp;index, &amp;MinOBB);</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(MaxTri</font><font size="2"> 
  &lt; MinOBB || MinTri &gt; MaxOBB)</p>
  </font>
  <blockquote>
    <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
    <font SIZE="2" COLOR="#0000ff">false</font><font size="2">;</p>
  </blockquote>
  </font>
  <p>¡@</p>
  <p><font SIZE="2" COLOR="#008000">//Projection axis: cross product of 
  triangle's normal and normal 3 of OBB</p>
  </font><font size="2">
  <p>CalculateProject(pTri, CrossProduct((*pTri).n, pOBB-&gt;Nz), pValTri);</p>
  <p>MaxProjVal(3, pValTri, &amp;index, &amp;MaxTri);</p>
  <p>MinProjVal(3, pValTri, &amp;index, &amp;MinTri);</p>
  <p>CalculateProjection(pOBB, CrossProduct((*pTri).n, pOBB-&gt;Nz), pValOBB);</p>
  <p>MaxProjVal(8, pValOBB, &amp;index, &amp;MaxOBB);</p>
  <p>MinProjVal(8, pValOBB, &amp;index, &amp;MinOBB);</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">if</font><font size="2">(MaxTri</font><font size="2"> 
  &lt; MinOBB || MinTri &gt; MaxOBB)</p>
  </font>
  <blockquote>
    <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
    <font SIZE="2" COLOR="#0000ff">false</font><font size="2">;</font></p>
  </blockquote>
  <p>¡@</p>
  <p><font SIZE="2" COLOR="#008000">//No separating axis, thus collision occurs.</p>
  </font>
  <p><font SIZE="2" COLOR="#0000ff">return</font><font SIZE="2"> </font>
  <font SIZE="2" COLOR="#0000ff">true</font><font size="2">;</p>
</blockquote>
<p>}</p>
</font>
<p align="justify">¡@</p>
<p align="justify">To prevent the OBB getting locked inside the obstacle, for 
each advancing loop of it, there is a copy of its previous state valuables 
(displacement, velocity and momentum etc).&nbsp; When the collision occurs, its 
current state valuables will be restored to the previous one, so as to ensure 
that the OBB will never go inside the obstacle.&nbsp; This simple idea is shown 
in figure 1.2, the rectangle in purple is the OBB of a dynamics object at a 
certain instant and will be restored to the dotted previous one.</p>
<p align="justify">¡@</p>
<p align="justify">¡@</p>
<p align="center"><img border="0" src="BSPCD.jpg" width="450" height="374"></p>
<p align="center"><b>Figure 1.2</b></p>

<p align="center">¡@</p>
<p align="center"><font face="Times New Roman" size="4"><b><span lang="en-us">
<a href="Work.htm">Back</a></span></b></font></p>

</body>

</html>
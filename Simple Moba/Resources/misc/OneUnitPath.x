xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Plane_001 {
    FrameTransformMatrix {
       1.000000, 0.000000, 0.000000, 0.000000,
       0.000000,-0.000000, 1.000000, 0.000000,
       0.000000,-1.000000,-0.000000, 0.000000,
       0.000000, 0.000000, 0.500000, 1.000000;;
    }
    Mesh { // Plane_001 mesh
      4;
      -0.500000;-0.500000; 0.000000;,
       0.500000;-0.500000; 0.000000;,
       0.500000; 0.500000; 0.000000;,
      -0.500000; 0.500000; 0.000000;;
      1;
      4;3,2,1,0;;
      MeshNormals { // Plane_001 normals
        4;
         0.000000; 0.000000; 1.000000;,
         0.000000; 0.000000; 1.000000;,
         0.000000; 0.000000; 1.000000;,
         0.000000; 0.000000; 1.000000;;
        1;
        4;3,2,1,0;;
      } // End of Plane_001 normals
      MeshTextureCoords { // Plane_001 UV coordinates
        4;
         0.000000; 1.000000;,
         1.000000; 1.000000;,
         1.000000; 0.000000;,
         0.000000; 0.000000;;
      } // End of Plane_001 UV coordinates
      MeshMaterialList { // Plane_001 material list
        1;
        1;
        0;
        Material MyPlaneMaterial {
           0.640000; 0.640000; 0.640000; 0.000000;;
           249.019608;
           0.400000; 0.400000; 0.400000;;
           0.000000; 0.000000; 0.000000;;
          TextureFilename {"OneUnitPath.png";}
        }
      } // End of Plane_001 material list
    } // End of Plane_001 mesh
  } // End of Plane_001
} // End of Root


from numpy import asarray
from mayavi.mlab import triangular_mesh
    
def read_off(file):
    if 'OFF' != file.readline().strip():
        raise('Not a valid OFF header')
    n_verts, n_faces, n_dontknow = tuple([int(s) for s in file.readline().strip().split(' ')])
    verts = [[float(s) for s in file.readline().strip().split(' ')] for i_vert in range(n_verts)]
    faces = [[int(s) for s in file.readline().strip().split(' ')][1:] for i_face in range(n_faces)]
    verts = asarray(verts)
    faces = asarray(faces)
    return verts, faces
    
def plot_mayavi_off(vertices, faces):
    return triangular_mesh(vertices[:,0], vertices[:,1], vertices[:,2], faces, color=(0.5, 0.5, 0.5), opacity=0.2)

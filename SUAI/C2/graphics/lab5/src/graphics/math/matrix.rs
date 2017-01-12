#![macro_use]
use std::ops::{Mul, MulAssign, Index, IndexMut, Deref, DerefMut};
use std::clone::Clone;
use std::mem;

#[derive(Debug)]
pub struct MatrixPair(pub Matrix, pub Matrix);

impl Deref for MatrixPair {
    type Target = Matrix;
    fn deref(&self) -> &Matrix {
        &self.0
    }
}

impl DerefMut for MatrixPair {
    fn deref_mut(&mut self) -> &mut Matrix {
        &mut self.0
    }
}

impl MatrixPair {
    pub fn swap(&mut self) {
        mem::swap(&mut self.0, &mut self.1);
    }
}


#[derive(Debug)]
pub enum Matrix {
     Static([[f64; 4]; 4]),
     Dynamic(Vec<[f64; 4]>),
}

impl Matrix {
    pub fn len(&self) -> usize {
        match *self {
            Matrix::Static(..) => 4,
            Matrix::Dynamic(ref vec) => vec.len(),
        }
    }
}

impl Index<usize> for Matrix {
    type Output = [f64; 4];
    fn index(&self, idx: usize) -> &Self::Output {
        match *self {
            Matrix::Static(ref array) => &array[idx],
            Matrix::Dynamic(ref vec)  => &vec[idx],
        }
    }
}

impl IndexMut<usize> for Matrix {
    fn index_mut(&mut self, idx: usize) -> &mut Self::Output {
        match *self {
            Matrix::Static(ref mut array) => &mut array[idx],
            Matrix::Dynamic(ref mut vec)  => &mut vec[idx],
        }
    }
}

impl Clone for Matrix {
    fn clone(&self) -> Matrix {
        match *self {
            Matrix::Static(array) => Matrix::Static(array),
            Matrix::Dynamic(ref vec)  => Matrix::Dynamic(vec.clone()),
        }
    }
}

impl Mul for Matrix {
    type Output = Matrix;

    fn mul(self, _rhs: Matrix) -> Matrix {
        use std::cmp;

        let rows_cnt = cmp::max(_rhs.len(), self.len());
        let mut new = Matrix::null_matrix(rows_cnt);
        for row in 0..rows_cnt {
            for col in 0..4 {
                for inner in 0..4 {
                    new[row][col] += self[row][inner] * _rhs[inner][col];
                }
            }
        }

        return new;
    }
}

impl MulAssign<Matrix> for MatrixPair {
    fn mul_assign(&mut self, _rhs: Matrix) {
        use std::cmp;
        let rows_cnt = cmp::max(self.0.len(), _rhs.len());

        for row in 0..rows_cnt {
            for col in 0..4 {
                self.1[row][col] = 0.0;
            }
        }

        for row in 0..rows_cnt {
            for col in 0..4 {
                for inner in 0..4 {
                    self.1[row][col] += self.0[row][inner] * _rhs[inner][col];
                }
            }
        }

        self.swap()
    }
}

#[allow(dead_code)]
impl Matrix {
    #[inline]
    pub fn null_matrix(rows: usize) -> Matrix {
        let mut vec = Vec::with_capacity(rows);
        for _ in 0..rows {
            vec.push([0.0; 4]);
        }
        Matrix::Dynamic(vec)
    }

    #[inline]
    pub fn identity_matrix() -> Matrix {
        Matrix::Static(
            [[1.0, 0.0, 0.0, 0.0],
             [0.0, 1.0, 0.0, 0.0],
             [0.0, 0.0, 1.0, 0.0],
             [0.0, 0.0, 0.0, 1.0]]
        )
    }

    #[inline]
    pub fn translation_matrix(dx: f64, dy: f64) -> Matrix {
        Matrix::Static(
            [[1.0, 0.0, 0.0, 0.0],
             [0.0, 1.0, 0.0, 0.0],
             [dx,  dy,  1.0, 0.0],
             [0.0, 0.0, 0.0, 1.0]]
        )
    }

    #[inline]
    pub fn scale_matrix(sx: f64, sy: f64) -> Matrix {
        Matrix::Static(
            [[sx,  0.0, 0.0, 0.0],
             [0.0, sy,  0.0, 0.0],
             [0.0, 0.0, 1.0, 0.0],
             [0.0, 0.0, 0.0, 1.0]]
        )
    }

    #[inline]
    pub fn rotation_matrix(angle: f64) -> Matrix {
        let a = angle.to_radians();
        Matrix::Static(
            [[ a.cos(), a.sin(), 0.0, 0.0],
             [-a.sin(), a.cos(), 0.0, 0.0],
             [0.0,      0.0,     1.0, 0.0],
             [0.0,      0.0,     0.0, 1.0]]
        )
    }

    #[inline]
    pub fn identity_matrix_3D() -> Matrix {
        Matrix::Static(
            [[1.0, 0.0, 0.0, 0.0],
             [0.0, 1.0, 0.0, 0.0],
             [0.0, 0.0, 1.0, 0.0],
             [0.0, 0.0, 0.0, 1.0]]
        )
    }

    #[inline]
    pub fn translation_matrix_3D(dx: f64, dy: f64, dz: f64) -> Matrix {
        Matrix::Static(
            [[1.0, 0.0, 0.0, 0.0],
             [0.0, 1.0, 0.0, 0.0],
             [0.0, 0.0, 1.0, 0.0],
             [dx,  dy,  dz,  1.0]]
        )
    }

    #[inline]
    pub fn scale_matrix_3D(sx: f64, sy: f64, sz: f64) -> Matrix {
        Matrix::Static(
            [[sx,  0.0, 0.0, 0.0],
             [0.0, sy,  0.0, 0.0],
             [0.0, 0.0, sz , 0.0],
             [0.0, 0.0, 0.0, 1.0]]
        )
    }

    #[inline]
    pub fn rotation_matrix_x(angle: f64) -> Matrix {
        let a = angle.to_radians();
        Matrix::Static(
            [[1.0, 0.0,     0.0,     0.0],
             [0.0, a.cos(), a.sin(), 0.0],
             [0.0,-a.sin(), a.cos(), 0.0],
             [0.0, 0.0,     0.0,     1.0]]
        )
    }

    #[inline]
    pub fn rotation_matrix_y(angle: f64) -> Matrix {
        let a = angle.to_radians();
        Matrix::Static(
            [[a.cos(), 0.0,-a.sin(), 0.0],
             [0.0,     1.0, 0.0,     0.0],
             [a.sin(), 0.0, a.cos(), 0.0],
             [0.0, 0.0,     0.0,     1.0]]
        )
    }

    #[inline]
    pub fn rotation_matrix_z(angle: f64) -> Matrix {
        let a = angle.to_radians();
        Matrix::Static(
            [[a.cos(),   a.sin(), 0.0, 0.0],
             [-a.sin(),  a.cos(), 0.0, 0.0],
             [0.0,       0.0,     1.0, 0.0],
             [0.0,       0.0,     0.0, 1.0]]
        )
    }

    #[inline]
    pub fn orthographic_projection_matrix() -> Matrix {
        let a = 45.0_f64.to_radians();
        let l = -0.5;
        Matrix::Static(
            [[1.0, 0.0, 0.0, 0.0],
             [0.0, 1.0, 0.0, 0.0],
             [l * a.cos() , l * a.sin(), 0.0, 0.0],
             [0.0, 0.0, 0.0, 1.0]]
        )
    }

    #[inline]
    pub fn camera_matrix(fov: f64, aspect: f64, near: f64, far: f64) -> Matrix {
        let scale = 1.0 / (fov * 0.5_f64.to_radians()).tan(); 
        Matrix::Static(
            [[scale, 0.0,   0.0,                  0.0],
             [0.0,   scale, 0.0,                  0.0],
             [0.0,   0.0,   -far/(far-near),     -1.0],
             [0.0,   0.0,   -far*near/(far-near), 0.0]]
        )
    }

}

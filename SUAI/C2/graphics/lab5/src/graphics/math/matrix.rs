#![macro_use]
use std::ops::Mul;
use std::clone::Clone;

#[derive(Debug)]
pub struct Matrix {
    pub matrix: Vec<[f64; 4]>,
}

impl Matrix {
    pub fn new(rows: Vec<[f64; 4]>) -> Matrix {
        Matrix {
            matrix: rows
        }
    }
}

impl Clone for Matrix {
    fn clone(&self) -> Matrix {
        Matrix::new(
            self.matrix.clone()
        )
    }
}

impl Mul for Matrix {
    type Output = Matrix;

    fn mul(self, _rhs: Matrix) -> Matrix {
        use std::cmp;
        let rows_cnt = cmp::max(_rhs.matrix.len(), self.matrix.len());
        let mut new = Matrix::null_matrix(rows_cnt);
        for row in 0..rows_cnt {
            for col in 0..4 {
                for inner in 0..4 {
                    new.matrix[row][col] += self.matrix[row][inner] *
                                           _rhs.matrix[inner][col];
                }
            }
        }

        return new;
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
        Matrix::new(vec)
    }

    #[inline]
    pub fn identity_matrix() -> Matrix {
        Matrix::new(
            vec![[1.0, 0.0, 0.0, 0.0],
                 [0.0, 1.0, 0.0, 0.0],
                 [0.0, 0.0, 1.0, 0.0]]
        )
    }

    #[inline]
    pub fn translation_matrix(dx: f64, dy: f64) -> Matrix {
        Matrix::new(
            vec![[1.0, 0.0, 0.0, 0.0],
                 [0.0, 1.0, 0.0, 0.0],
                 [dx,  dy,  1.0, 0.0]]
        )
    }

    #[inline]
    pub fn scale_matrix(sx: f64, sy: f64) -> Matrix {
        Matrix::new(
            vec![[sx,  0.0, 0.0, 0.0],
                 [0.0, sy,  0.0, 0.0],
                 [0.0, 0.0, 1.0, 0.0]]
        )
    }

    #[inline]
    pub fn rotation_matrix(angle: f64) -> Matrix {
        let a = angle.to_radians();
        Matrix::new(
            vec![[ a.cos(), a.sin(), 0.0, 0.0],
                 [-a.sin(), a.cos(), 0.0, 0.0],
                 [0.0,      0.0,     1.0, 0.0]]
        )
    }

    #[inline]
    pub fn identity_matrix_3D() -> Matrix {
        Matrix::new(
            vec![[1.0, 0.0, 0.0, 0.0],
                 [0.0, 1.0, 0.0, 0.0],
                 [0.0, 0.0, 1.0, 0.0],
                 [0.0, 0.0, 0.0, 1.0]]
        )
    }

    #[inline]
    pub fn translation_matrix_3D(dx: f64, dy: f64, dz: f64) -> Matrix {
        Matrix::new(
            vec![[1.0, 0.0, 0.0, 0.0],
                 [0.0, 1.0, 0.0, 0.0],
                 [0.0, 0.0, 1.0, 0.0],
                 [dx,  dy,  dz,  1.0]]
        )
    }

    #[inline]
    pub fn scale_matrix_3D(sx: f64, sy: f64, sz: f64) -> Matrix {
        Matrix::new(
            vec![[sx,  0.0, 0.0, 0.0],
                 [0.0, sy,  0.0, 0.0],
                 [0.0, 0.0, sz , 0.0],
                 [0.0, 0.0, 0.0, 1.0]]
        )
    }

    #[inline]
    pub fn rotation_matrix_x(angle: f64) -> Matrix {
        let a = angle.to_radians();
        Matrix::new(
            vec![[1.0, 0.0,     0.0,     0.0],
                 [0.0, a.cos(), a.sin(), 0.0],
                 [0.0,-a.sin(), a.cos(), 0.0],
                 [0.0, 0.0,     0.0,     1.0]]
        )
    }

    #[inline]
    pub fn rotation_matrix_y(angle: f64) -> Matrix {
        let a = angle.to_radians();
        Matrix::new(
            vec![[a.cos(), 0.0,-a.sin(), 0.0],
                 [0.0,     1.0, 0.0,     0.0],
                 [a.sin(), 0.0, a.cos(), 0.0],
                 [0.0, 0.0,     0.0,     1.0]]
        )
    }

    #[inline]
    pub fn rotation_matrix_z(angle: f64) -> Matrix {
        let a = angle.to_radians();
        Matrix::new(
            vec![[a.cos(),   a.sin(), 0.0, 0.0],
                 [-a.sin(),  a.cos(), 0.0, 0.0],
                 [0.0,       0.0,     1.0, 0.0],
                 [0.0,       0.0,     0.0, 1.0]]
        )
    }

    #[inline]
    pub fn orthographic_projection_matrix() -> Matrix {
        Matrix::new(
            vec![[1.0, 0.0, 0.0, 0.0],
                 [0.0, 1.0, 0.0, 0.0],
                 [0.0, 0.0, 0.0, 0.0],
                 [0.0, 0.0, 0.0, 1.0]]
        )
    }

    #[inline]
    pub fn camera_matrix(fov: f64, aspect: f64, near: f64, far: f64) -> Matrix {
        let fDepth = far - near;
        let fDepth = 1.0 / fDepth;

        let r1 = 1.0/(0.5*fov).tan();
        Matrix::new(
            vec![[r1, 0.0,  0.0,          0.0],
                 [0.0,       r1/aspect,   0.0,          0.0],
                 [0.0,       0.0,  far * fDepth, (-far*near) * fDepth],
                 [0.0,       0.0,  1.0,          0.0]]
        )
    }

}

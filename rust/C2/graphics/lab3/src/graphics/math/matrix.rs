#![macro_use]
use std::ops::Mul;

pub struct Matrix {
    pub matrix: Vec<[f32; 3]>,
}

impl Matrix {
    pub fn new(rows: Vec<[f32; 3]>) -> Matrix {
        Matrix {
            matrix: rows
        }
    }
}

impl Mul for Matrix {
    type Output = Matrix;

    fn mul(self, _rhs: Matrix) -> Matrix {
        let rows_cnt = self.matrix.len();
        let mut new = Matrix::null_matrix(rows_cnt);
        for row in 0..rows_cnt {
            for col in 0..3 {
                for inner in 0..3 {
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
            vec.push([0.0, 0.0, 0.0]);
        }
        Matrix::new(vec)
    }

    #[inline]
    pub fn identity_matrix() -> Matrix {
        Matrix::new(
            vec![[1.0, 0.0, 0.0],
                 [0.0, 1.0, 0.0],
                 [0.0, 0.0, 1.0]]
        )
    }

    #[inline]
    pub fn translation_matrix(dx: f32, dy: f32) -> Matrix {
        Matrix::new(
            vec![[1.0, 0.0, 0.0],
                 [0.0, 1.0, 0.0],
                 [dx,  dy,  1.0]]
        )
    }

    #[inline]
    pub fn scale_matrix(sx: f32, sy: f32) -> Matrix {
        Matrix::new(
            vec![[sx,  0.0, 0.0],
                 [0.0, sy,  0.0],
                 [0.0, 0.0, 1.0]]
        )
    }

    #[inline]
    pub fn rotation_matrix(angle: f32) -> Matrix {
        let a = angle.to_radians();
        Matrix::new(
            vec![[ a.cos(), a.sin(), 0.0],
                 [-a.sin(), a.cos(), 0.0],
                 [0.0,      0.0,     1.0]]
        )
    }
}

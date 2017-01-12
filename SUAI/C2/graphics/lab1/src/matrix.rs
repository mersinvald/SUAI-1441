#![macro_use]
use std::ops::Mul;

pub struct Matrix {
    pub matrix: [[f32; 3]; 3],
}

macro_rules! matrix {
    ($x: expr) => {
        Matrix { matrix: $x }
    };
}

impl Mul for Matrix {
    type Output = Matrix;

    fn mul(self, _rhs: Matrix) -> Matrix {
        let mut new = null_matrix();
        for row in 0..3 {
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

#[inline]
pub fn null_matrix() -> Matrix {
    matrix!([[0.0, 0.0, 0.0],
             [0.0, 0.0, 0.0],
             [0.0, 0.0, 0.0]])
}

#[inline]
pub fn identity_matrix() -> Matrix {
    matrix!([[1.0, 0.0, 0.0],
             [0.0, 1.0, 0.0],
             [0.0, 0.0, 1.0]])
}

#[inline]
pub fn translation_matrix(dx: f32, dy: f32) -> Matrix {
    matrix!([[1.0, 0.0, 0.0],
             [0.0, 1.0, 0.0],
             [dx,  dy,  1.0]])
}

#[inline]
pub fn scale_matrix(sx: f32, sy: f32) -> Matrix {
    matrix!([[sx,  0.0, 0.0],
             [0.0, sy,  0.0],
             [0.0, 0.0, 1.0]])
}

#[inline]
pub fn rotation_matrix(angle: f32) -> Matrix {
    use std::f32::consts::PI;
    let a = (angle * PI) / 180.0;
    matrix!([[ a.cos(), a.sin(), 0.0],
             [-a.sin(), a.cos(), 0.0],
             [0.0,      0.0,     1.0]])
}

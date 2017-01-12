use sdl2::render::Renderer;
use std;

pub mod line;
pub mod pyramide;

use graphics::math::matrix::Matrix;

#[derive(Debug)]
pub struct Point2D {
    pub x: f64,
    pub y: f64,
}

#[derive(Debug)]
pub struct Point3D {
    pub x: f64,
    pub y: f64,
    pub z: f64
}

impl Point2D {
    pub fn new(x: f64, y: f64) -> Point2D {
        Point2D {
            x: x,
            y: y,
        }
    }
}

impl Point3D {
    pub fn new(x: f64, y: f64, z: f64) -> Point3D {
        Point3D {
            x: x,
            y: y,
            z: z
        }
    }
}

impl<'a> std::convert::From<&'a Point3D> for Point2D {
    fn from(f: &Point3D) -> Self {
        Point2D::new (
            f.x,
            f.y,
        )
    }
}

impl<'a> std::convert::From<&'a [f64; 4]> for Point2D {
    fn from(f: &[f64; 4]) -> Self {
        Point2D::new (
            f[0],
            f[1],
        )
    }
}

impl std::clone::Clone for Point2D {
    fn clone(&self) -> Point2D {
        Point2D::new(self.x, self.y)
    }
}

impl std::clone::Clone for Point3D {
    fn clone(&self) -> Point3D {
        Point3D::new(self.x, self.y, self.z)
    }
}

pub trait Primitive2D {
    /* Getting and setting via matrices, for affine transform */
    fn to_matrix(&self) -> Matrix;
    fn from_matrix(&mut self, m: &Matrix);

    /* Acnhor point is the local coordinates start point */
    fn anchor_point(&self) -> Point2D;
    fn set_anchor_point(&mut self, anchor: &Point2D);

    /* Affine Transformations */
    fn translate(&mut self, dx: f64, dy: f64) {
        let obj = self.to_matrix();
        let mut anchor = self.anchor_point();

        self.from_matrix(
          &(obj *
            Matrix::translation_matrix(-anchor.x, -anchor.y) *
            Matrix::translation_matrix(dx, dy) *
            Matrix::translation_matrix(anchor.x, anchor.y))
        );

        // Moving anchor point by dx and dy
        anchor.x += dx;
        anchor.y += dy;

        self.set_anchor_point(&anchor);
    }

    fn scale(&mut self, sx: f64, sy: f64) {
        let obj = self.to_matrix();
        let anchor = self.anchor_point();

        self.from_matrix(
          &(obj *
            Matrix::translation_matrix(-anchor.x, -anchor.y) *
            Matrix::scale_matrix(sx, sy) *
            Matrix::translation_matrix(anchor.x, anchor.y))
        );
    }

    fn rotate(&mut self, angle: f64) {
        let obj = self.to_matrix();
        let anchor = self.anchor_point();

        self.from_matrix(
          &(obj *
            Matrix::translation_matrix(-anchor.x, -anchor.y) *
            Matrix::rotation_matrix(angle) *
            Matrix::translation_matrix(anchor.x, anchor.y))
        );
    }

    /* Draw the object on screen */
    fn draw(&self, renderer: &Renderer);

    fn fill(&self, renderer: &Renderer);
}


pub trait Primitive3D {
    /* Getting and setting via matrices, for affine transform */
    fn to_matrix(&self) -> Matrix;
    fn from_matrix(&mut self, m: &Matrix);

    /* Acnhor point is the local coordinates start point */
    fn anchor_point(&self) -> Point3D;
    fn set_anchor_point(&mut self, anchor: &Point3D);

    /* Affine Transformations */
    fn translate(&mut self, dx: f64, dy: f64, dz: f64) {
        let obj = self.to_matrix();
        let mut anchor = self.anchor_point();

        self.from_matrix(
          &(obj *
            Matrix::translation_matrix_3D(-anchor.x, -anchor.y, -anchor.z) *
            Matrix::translation_matrix_3D(dx, dy, dz) *
            Matrix::translation_matrix_3D(anchor.x, anchor.y, anchor.z))
        );

        // Moving anchor point by dx and dy
        anchor.x += dx;
        anchor.y += dy;
        anchor.z += dz;

        self.set_anchor_point(&anchor);
    }

    fn scale(&mut self, sx: f64, sy: f64, sz: f64) {
        let obj = self.to_matrix();
        let anchor = self.anchor_point();

        self.from_matrix(
          &(obj *
            Matrix::translation_matrix_3D(-anchor.x, -anchor.y, -anchor.z) *
            Matrix::scale_matrix_3D(sx, sy, sz) *
            Matrix::translation_matrix_3D(anchor.x, anchor.y, anchor.z))
        );
    }

    fn rotate(&mut self, ax: f64, ay: f64, az: f64) {
        let obj = self.to_matrix();
        let anchor = self.anchor_point();

        self.from_matrix(
          &(obj *
            Matrix::translation_matrix_3D(-anchor.x, -anchor.y, -anchor.z) *
            Matrix::rotation_matrix_x(ax) *
            Matrix::rotation_matrix_y(ay) *
            Matrix::rotation_matrix_z(az) *
            Matrix::translation_matrix_3D(anchor.x, anchor.y, anchor.z))
        );
    }

    /* Draw the object on screen */
    fn draw(&self, renderer: &Renderer);

    fn fill(&self, renderer: &Renderer);
}

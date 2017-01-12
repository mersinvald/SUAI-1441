use sdl2::render::Renderer;
use std;

pub mod line;
pub mod pyramide;

use graphics::math::matrix::*;

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
    fn inner_matrix(&mut self) -> &mut MatrixPair           { unimplemented!() }
    fn load_matrix(&mut self)                               { unimplemented!() }

    /* Acnhor point is the local coordinates start point */
    fn anchor_point(&self) -> Point2D                       { unimplemented!() }
    fn set_anchor_point(&mut self, anchor: &Point2D)        { unimplemented!() }

    /* Draw the object on screen */
    fn draw(&mut self, renderer: &Renderer)                 { unimplemented!() }
    fn fill(&mut self, renderer: &Renderer)                 { unimplemented!() }

    /* Affine Transformations */
    fn translate(&mut self, dx: f64, dy: f64) {
        let mut anchor = self.anchor_point();
        {
            let mut matrix = self.inner_matrix();

            *matrix *= Matrix::translation_matrix(-anchor.x, -anchor.y);
            *matrix *= Matrix::translation_matrix(dx, dy);
            *matrix *= Matrix::translation_matrix(anchor.x, anchor.y);
        }
        self.load_matrix();

        // Moving anchor point by dx and dy
        anchor.x += dx;
        anchor.y += dy;

        self.set_anchor_point(&anchor);
    }

    fn scale(&mut self, sx: f64, sy: f64) {
        let anchor = self.anchor_point();
        {
            let matrix = self.inner_matrix();

            *matrix *= Matrix::translation_matrix(-anchor.x, -anchor.y);
            *matrix *= Matrix::scale_matrix(sx, sy);
            *matrix *= Matrix::translation_matrix(anchor.x, anchor.y);
        }
        self.load_matrix();
    }

    fn rotate(&mut self, angle: f64) {
        let anchor = self.anchor_point();
        {
            let matrix = self.inner_matrix();

            *matrix *= Matrix::translation_matrix(-anchor.x, -anchor.y);
            *matrix *= Matrix::rotation_matrix(angle);
            *matrix *= Matrix::translation_matrix(anchor.x, anchor.y);
        }
        self.load_matrix();
    }
}


pub trait Primitive3D {
    /* Getting and setting via matrices, for affine transform */
    fn inner_matrix(&mut self) -> &mut MatrixPair           { unimplemented!() }
    fn load_matrix(&mut self)                               { unimplemented!() }

    /* Acnhor point is the local coordinates start point */
    fn anchor_point(&self) -> Point3D                       { unimplemented!() }
    fn set_anchor_point(&mut self, anchor: &Point3D)        { unimplemented!() }

    /* Draw the object on screen */
    fn draw(&mut self, renderer: &Renderer)                 { unimplemented!() }
    fn fill(&mut self, renderer: &Renderer)                 { unimplemented!() }

    /* Affine Transformations */
    fn translate(&mut self, dx: f64, dy: f64, dz: f64) {
        let mut anchor = self.anchor_point();
        {
            let mut matrix = self.inner_matrix();

            *matrix *= Matrix::translation_matrix_3D(-anchor.x, -anchor.y, -anchor.z);
            *matrix *= Matrix::translation_matrix_3D(dx, dy, dz);
            *matrix *= Matrix::translation_matrix_3D(anchor.x, anchor.y, anchor.z);
        }
        self.load_matrix();

        // Moving anchor point by dx and dy
        anchor.x += dx;
        anchor.y += dy;
        anchor.z += dz;

        self.set_anchor_point(&anchor);
    }

    fn scale(&mut self, sx: f64, sy: f64, sz: f64) {    
        let anchor = self.anchor_point();
        {
            let mut matrix = self.inner_matrix();

            *matrix *= Matrix::translation_matrix_3D(-anchor.x, -anchor.y, -anchor.z);
            *matrix *= Matrix::scale_matrix_3D(sx, sy, sz);
            *matrix *= Matrix::translation_matrix_3D(anchor.x, anchor.y, anchor.z);
        }
        self.load_matrix();
    }

    fn rotate(&mut self, ax: f64, ay: f64, az: f64) {
        let anchor = self.anchor_point();
        {
            let mut matrix = self.inner_matrix();

            *matrix *= Matrix::translation_matrix_3D(-anchor.x, -anchor.y, -anchor.z);
            *matrix *= Matrix::rotation_matrix_x(ax);
            *matrix *= Matrix::rotation_matrix_y(ay);
            *matrix *= Matrix::rotation_matrix_z(az);
            *matrix *= Matrix::translation_matrix_3D(anchor.x, anchor.y, anchor.z);
        }
        self.load_matrix();
    }
}

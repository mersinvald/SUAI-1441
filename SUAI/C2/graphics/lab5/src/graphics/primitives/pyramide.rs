use sdl2::pixels::Color;
use sdl2::render::Renderer;
use sdl2_gfx::primitives::DrawRenderer;

use graphics::primitives::*;
use graphics::math::matrix::*;

#[derive(Debug)]
pub struct Pyramide {
    pub points: Vec<Point3D>,
    anchor: Point3D,
    colors:  Vec<Color>
}

impl Pyramide {
    pub fn new(center: &Point3D, w: f64, h: f64, colors: Vec<Color>) -> Pyramide {
        use std::f64::*;

        let mut vertices = Vec::with_capacity(5);

        // Top vertex
        vertices.push(
            Point3D::new(center.x, center.y - h / 2.0, center.z)
        );

        // Bottom quad
        let by = center.y + h / 2.0;
        let radius = w / 2.0;
        for i in 0..4 {
            let i = i as f64;
            vertices.push(
                Point3D::new(
                    center.x + radius * (2.0 * consts::PI * i / 4.0).cos(),
                    by,
                    center.z + radius * (2.0 * consts::PI * i / 4.0).sin(),
                )
            );
        }

        println!("{:?}", vertices);

        Pyramide {
            points: vertices,
            anchor: center.clone(),
            colors: colors
        }
    }
}

impl Primitive3D for Pyramide {
    fn to_matrix(&self) -> Matrix {
        let p = &self.points;
        Matrix::new(
            vec![[p[0].x, p[0].y, p[0].z, 1.0],
                 [p[1].x, p[1].y, p[1].z, 1.0],
                 [p[2].x, p[2].y, p[2].z, 1.0],
                 [p[3].x, p[3].y, p[3].z, 1.0],
                 [p[4].x, p[4].y, p[4].z, 1.0]]
        )
    }

    // TODO: From Vec to Point
    fn from_matrix(&mut self, m: &Matrix) {
        println!("{:?}", self);
        println!("{:?}", m);
        for i in 0..5 {
            self.points[i].x = m.matrix[i][0];
            self.points[i].y = m.matrix[i][1];
            self.points[i].z = m.matrix[i][2];
        }
    }

    fn anchor_point(&self) -> Point3D {
        return self.anchor.clone();
    }

    fn set_anchor_point(&mut self, anchor: &Point3D) {
        self.anchor = anchor.clone();
    }

    fn draw(&self, renderer: &Renderer) {
        let m2d = self.to_matrix() * Matrix::camera_matrix(2.0, 1280.0/720.0, 0.0, 100.0);
        let top_2d = Point2D::from(&m2d.matrix[0]);

        for i in 0..5 {
            let next_index = if i == 4 { 1 } else { i + 1 };
            let p1_2d = Point2D::from(&m2d.matrix[i]);
            let p2_2d = Point2D::from(&m2d.matrix[next_index]);

            let t_line = line::Line::new(&top_2d, &p1_2d, self.colors[i % self.colors.len()]);
            let p_line = line::Line::new(&p1_2d, &p2_2d,  self.colors[next_index % self.colors.len()]);

            t_line.draw(renderer);
            p_line.draw(renderer);
        }
    }

    fn fill(&self, renderer: &Renderer) {
        let center_z = self.points.iter().fold(0.0, |sum, item| sum + item.z)
                     / self.points.len() as f64;

        let m2d = self.to_matrix() * Matrix::camera_matrix(2.0, 1280.0/720.0, 0.0, 100.0);

        let top = &self.points[0];
        let top_2d = Point2D::from(&m2d.matrix[0]);

        for i in 1..5 {
            let next_index = if i == 4 { 1 } else { i + 1 };
            let p1 = &self.points[i];
            let p2 = &self.points[next_index];
            let p1_2d = Point2D::from(&m2d.matrix[i]);
            let p2_2d = Point2D::from(&m2d.matrix[next_index]);

            let avg = (top.z + p1.z + p2.z) / 3.0;
            if avg > center_z {
                renderer.filled_trigon(
                    top_2d.x as i16,
                    top_2d.y as i16,
                    p1_2d.x as i16,
                    p1_2d.y as i16,
                    p2_2d.x as i16,
                    p2_2d.y as i16,
                    self.colors[i % self.colors.len()]
                ).unwrap();
            }
        }

        // Drawing Bottom
        let mut vx = Vec::with_capacity(4);
        let mut vy = Vec::with_capacity(4);

        let mut avg = 0.0;
        for i in 1..5 {
            let p = &self.points[i];
            let p_2d = Point2D::from(&m2d.matrix[i]);
            avg += p.z;
            vx.push(p_2d.x as i16);
            vy.push(p_2d.y as i16);
        }
        avg /= 4.0;

        if avg > center_z {
            renderer.filled_polygon(
                vx.as_slice(),
                vy.as_slice(),
                self.colors[5 % self.colors.len()]
            ).unwrap();
        }
    }
}

use sdl2::pixels::Color;
use sdl2::render::Renderer;
use sdl2_gfx::primitives::DrawRenderer;

use graphics::primitives::*;
use graphics::math::matrix::*;

#[derive(Debug)]
pub struct Pyramide {
    matrix: MatrixPair,
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

        // Construct 

        Pyramide {
            matrix: MatrixPair(Matrix::null_matrix(vertices.len()),
                               Matrix::null_matrix(vertices.len())),  
            points: vertices,
            anchor: center.clone(),
            colors: colors
        }
    }
}

impl Primitive3D for Pyramide {
    fn inner_matrix(&mut self) -> &mut MatrixPair {
        let p = &self.points;
        for i in 0..5 {
            self.matrix[i][0] = p[i].x;
            self.matrix[i][1] = p[i].y;
            self.matrix[i][2] = p[i].z;
            self.matrix[i][3] = 1.0;
        }
        &mut self.matrix
    }

    fn load_matrix(&mut self) {
        for i in 0..5 {
            self.points[i].x = self.matrix[i][0];
            self.points[i].y = self.matrix[i][1];
            self.points[i].z = self.matrix[i][2];
        }
    }

    fn anchor_point(&self) -> Point3D {
        return self.anchor.clone();
    }

    fn set_anchor_point(&mut self, anchor: &Point3D) {
        self.anchor = anchor.clone();
    }

    fn draw(&mut self, renderer: &Renderer) {
        let matrix = self.inner_matrix().clone();
        let m2d = matrix * Matrix::camera_matrix(2.0, 1280.0/720.0, 0.0, 100.0);
        let top_2d = Point2D::from(&m2d[0]);

        for i in 0..5 {
            let next_index = if i == 4 { 1 } else { i + 1 };
            let p1_2d = Point2D::from(&m2d[i]);
            let p2_2d = Point2D::from(&m2d[next_index]);

            let mut t_line = line::Line::new(&top_2d, &p1_2d, self.colors[i % self.colors.len()]);
            let mut p_line = line::Line::new(&p1_2d, &p2_2d,  self.colors[next_index % self.colors.len()]);

            t_line.draw(renderer);
            p_line.draw(renderer);
        }
    }

    fn fill(&mut self, renderer: &Renderer) {
        let center_z = self.points.iter().map(|item| item.z).sum::<f64>()
                     / self.points.len() as f64;

        let matrix = self.inner_matrix().clone();
        let m2d = matrix * Matrix::camera_matrix(2.0, 1280.0/720.0, 0.0, 100.0);

        let top = &self.points[0];
        let top_2d = Point2D::from(&m2d[0]);

        for i in 1..5 {
            let next_index = if i == 4 { 1 } else { i + 1 };
            let p1 = &self.points[i];
            let p2 = &self.points[next_index];
            let p1_2d = Point2D::from(&m2d[i]);
            let p2_2d = Point2D::from(&m2d[next_index]);

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
            let p_2d = Point2D::from(&m2d[i]);
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

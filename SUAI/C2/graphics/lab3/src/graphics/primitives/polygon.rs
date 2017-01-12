use sdl2::pixels::Color;
use sdl2::render::Renderer;

use graphics::primitives::line::Line;
use graphics::primitives::*;
use graphics::math::matrix::*;

pub struct Polygon {
    vertices: Vec<Point2D>,
    anchor:   Point2D,
    color:    Color
}

impl Polygon {
    pub fn new(center: &Point2D, radius: f32, cnt: usize, color: Color) -> Polygon {
        use std::f32::*;

        let mut vertices = Vec::with_capacity(cnt);

        for i in 0..cnt {
            let n = cnt as f32;
            let i = i as f32;
            vertices.push(
                Point2D::new(
                    center.x + radius * (2.0 * consts::PI * i / n).cos(),
                    center.y + radius * (2.0 * consts::PI * i / n).sin(),
                )
            )
        }

        Polygon {
            vertices: vertices,
            anchor: center.clone(),
            color: color,
        }
    }
}

impl Primitive2D for Polygon {
    fn to_matrix(&self) -> Matrix {
        let mut matrix = Vec::with_capacity(self.vertices.len());
        for vertex in &self.vertices {
            matrix.push([vertex.x, vertex.y, 1.0]);
        }

        Matrix::new(
            matrix
        )
    }

    fn from_matrix(&mut self, m: &Matrix) {
        for (i, row) in m.matrix.iter().enumerate() {
            self.vertices[i].x = row[0];
            self.vertices[i].y = row[1];
        }
    }

    fn anchor_point(&self) -> Point2D {
        self.anchor.clone()
    }

    fn set_anchor_point(&mut self, anchor: &Point2D) {
        self.anchor = anchor.clone();
    }

    fn draw(&self, renderer: &Renderer) {
        let mut lines = Vec::with_capacity(self.vertices.len() + 1);
        for i in 0..self.vertices.len() {
            let current_vertex = &self.vertices[i];
            let next_vertes = &self.vertices[(i+1) % self.vertices.len()];
            lines.push(
                Line::new(current_vertex, next_vertes, self.color)
            );
        }

        for line in lines {
            line.draw(renderer);
        }
    }

    fn fill(&self, renderer: &Renderer) {
        use std::f32;
        use sdl2_gfx::primitives::ll;
        use sdl2_gfx::primitives::ToColor;

        let is_inside = |x: i16, y: i16| -> bool {
            let v_cnt = self.vertices.len();
            let mut j = v_cnt - 1;
            let mut c = false;
            let p = &self.vertices;

            for i in 0..v_cnt {
                let pix = p[i].x as i16;
                let piy = p[i].y as i16;
                let pjx = p[j].x as i16;
                let pjy = p[j].y as i16;

                if (((piy <= y) && (y < pjy)) || ((pjy <= y) && (y < piy)))
                && (x > (pjx - pix) * (y - piy) / (pjy - piy) + pix) {
                    c = !c;
                }
                j = i;
            }
            return c;
        };

        let minx = self.vertices.iter().fold(f32::MAX, |min, val| {if val.x < min { val.x } else { min }} ) as i16;
        let miny = self.vertices.iter().fold(f32::MAX, |min, val| {if val.y < min { val.y } else { min }} ) as i16;
        let maxx = self.vertices.iter().fold(0.0, |max, val| {if val.x > max { val.x } else { max }} ) as i16;
        let maxy = self.vertices.iter().fold(0.0, |max, val| {if val.y > max { val.y } else { max }} ) as i16;

        let color = self.color.as_u32();

        for y in miny..maxy {
            for x in minx..maxx {
                if is_inside(x, y) {
                    unsafe {
                        ll::pixelColor(renderer.raw(), x, y, color);
                    }
                }
            }
        }
    }
}

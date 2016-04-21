extern crate sdl2;
use sdl2::pixels::Color;
use sdl2::rect::Point;
use sdl2::event::Event;
use sdl2::keyboard::Scancode::*;
use std::time::Duration;

mod matrix;
mod primitives;
use primitives::Primitive2D;

fn render_pixel(renderer: &mut sdl2::render::Renderer, x: i32, y: i32, color: Color) {
    let last_color = renderer.draw_color();
    renderer.set_draw_color(color);
    renderer.draw_point(Point::new(x, y)).unwrap();
    renderer.set_draw_color(last_color);
}

fn main() {
    let sdl_context   = sdl2::init().unwrap();
    let video_context = sdl_context.video().unwrap();

    let window = video_context.window("Graphics Task 1", 500, 500)
        .position_centered()
        .opengl()
        .build()
        .unwrap();

    let mut renderer = window.renderer().build().unwrap();

    renderer.set_draw_color(Color::RGB(0, 0, 0));
    renderer.clear();
    renderer.present();

    //let mut set_pixel =

    let mut events = sdl_context.event_pump().unwrap();

    let mut line1 = primitives::Line::new(
        100.0, 100.0, 350.0, 400.0, Color::RGB(0, 255, 0)
    );

    let mut line2 = primitives::Line::new(
        150.0, 100.0, 400.0, 400.0, Color::RGB(255, 0, 0)
    );

    'main:
    loop {
        for event in events.poll_iter() {
            match event {
                Event::Quit {..} => break 'main,
                _ => ()
            }
        }

        // Initializing variables
        let mut dx = 0.0;
        let mut dy = 0.0;
        let mut scale = 1.0;
        let mut angle = 0.0;

        // Poll through presed keys
        for key in events.keyboard_state().pressed_scancodes() {
            match key {
                Up      => dy -= 1.0,
                Down    => dy += 1.0,
                Right   => dx += 1.0,
                Left    => dx -= 1.0,
                W       => scale += 0.01,
                S       => scale -= 0.01,
                Q       => angle -= 1.0,
                E       => angle += 1.0,
                _       => (),
            }
        }

        // Do affine transformations
        line1.translate(dx, dy);
        line1.scale(scale, scale);
        line1.rotate(angle);

        line2.translate(dx, dy);
        line2.scale(scale, scale);
        line2.rotate(angle);

        renderer.clear();

        line1.draw(|x, y, color| render_pixel(&mut renderer, x, y, color));
        line2.draw_builtin_line(&mut renderer);

        renderer.present();

        std::thread::sleep(Duration::from_millis(10));
    }

}

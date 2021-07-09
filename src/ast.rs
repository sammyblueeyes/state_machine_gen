#[derive(Debug)]
pub struct State {
    pub name: String,
}

#[derive(Debug)]
pub struct Transition {
    pub name: String,
}

#[derive(Debug)]
pub struct Event {
    pub name: String,
}

#[derive(Debug)]
pub struct Digraph {
    pub name: String,
    pub states: Vec<State>,
    //events: Vec<Event>,

    // TODO transitions
}


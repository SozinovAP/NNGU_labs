package com.example.pract_ms_6

var timeLight = longArrayOf(1000, 1000, 1000).toCollection(ArrayList());

class TrafficLight {
    enum class TrafficLightState {
        RED, YELLOW, GREEN
    }

    private var state: TrafficLightState? = null
    private val states: ArrayList<TrafficLightState>;
    private var itr: ListIterator<TrafficLightState>;

    fun SetState(state: TrafficLightState) {
        itr = states.listIterator()
        while (itr.hasNext()) {
            val tempState = itr.next()
            if (tempState == state) {
                this.state = tempState
                break
            }
        }
    }

    fun ChangeTrafficLight(): TrafficLightState? {
        return if (itr.hasNext()) {
            state = itr.next()
            state
        } else {
            itr = states.listIterator()
            state = itr.next()
            state
        }
    }

    init {
        states = ArrayList()
        states.add(TrafficLightState.RED)
        states.add(TrafficLightState.YELLOW)
        states.add(TrafficLightState.GREEN)
        itr = states.listIterator()
    }
}
from services.base import ServiceBase
from helpers import round_up


class Server(ServiceBase):
    def update_config(self, agents: int,
                      storage: float,
                      traffic: float,
                      distributed: bool,
                      nodes: int,
                      p3value: float,
                      mail_traffic: float = None) -> None:

        if agents > 0 and storage > 0:
            self._replicas = min(p3value, 2)
        else:
            self._replicas = 0

        if distributed:
            self._memory = round(traffic * 0.5, 3)
        else:
            self._memory = 100

        self._cpu = 1
        if nodes > 0:
            self._storage = round_up(0.0019 * agents + 2.3154, 3)
        else:
            self._storage = 0
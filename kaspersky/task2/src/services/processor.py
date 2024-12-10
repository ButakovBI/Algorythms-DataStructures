import math

from services.base import ServiceBase
from helpers import round_up


class Processor(ServiceBase):
    def update_config(self, agents: int,
                      storage: float,
                      traffic: float,
                      distributed: bool,
                      nodes: int,
                      mail_traffic: float = None) -> None:

        if agents > 0 and storage > 0:
            self._replicas = 3 if distributed else 0
        else:
            self._replicas = 0

        self._memory = traffic * 0.5 if distributed else 100
        self._cpu = 3

        if nodes > 0:
            self._storage = round_up(-4.25877 + 0.98271 * math.log(agents), 3)
        else:
            self._storage = 0
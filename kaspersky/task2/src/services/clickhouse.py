from services.base import ServiceBase
from helpers import round_up


class Clickhouse(ServiceBase):
    def update_config(self, agents: int,
                      storage: float,
                      distributed: bool,
                      traffic: float = None,
                      mail_traffic: float = None,
                      nodes: int = None) -> None:

        if agents > 0:
            if distributed:
                self._replicas = max(round(agents / 15000), 1)
            else:
                self._replicas = 1
        else:
            self._replicas = 0

        if distributed:
            self._memory = round(storage * 1.6, 3)
        else:
            self._memory = 100

        self._cpu = 1
        self._storage = round_up(0.0000628 * agents + 0.6377, 3) if distributed else 0